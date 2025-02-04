package bot1

import battlecode.common.*;

public class Comms {
    static RobotController rc;
    static MapLocation sectorSize;

    static int numSectors;
    static int[] thresholds = {0, 1, 2, 3, 5, 10, 50};

    int H, W;

    static void init(RobotController r) {
        H = rc.getMapHeight();
        W = rc.getMapWidth();
        rc = r;
        int numRows = H/Constants.gridDimensions;
        int numCols = W/Constants.gridDimensions;
        if (H%Constants.gridDimensions != 0) {
            numRows++;
        }
        if (W % Constants.gridDimensions != 0) {
            numCols ++;
        }
        numSectors = numRows*numCols;
        sectorSize = new MapLocation(numCols, numRows);
    }
    public MapLocation getSectorDimensions() {
        return sectorSize;
    }

    public int getSector(MapLocation loc) {
        return (loc.x/Constants.gridDimensions)+(loc.y/Constants.gridDimensions)*sectorSize.x;
    }
    void reportHostile(robotInfo enemy) {
        MapLocation loc = enemy.location;
        int sec = getSector(loc);
        int inx = Constants.hostileStart+(sec/16);
        int g = rc.readSharedArray(inx);
        int val = 1&(g>>(inx%16));
        if (val == 0) {
            g += (1<<(inx%16));
            rc.writeSharedArray(inx, g);
        }
    }
    void reset() {
        for (int i = 0; i < 8; i++) {
            rc.writeSharedArray(Constants.hostileStart+i);
        }
    }
    public MapLocation getSectorCentre(int sec) {
        MapLocation ans;
        ans.y = (sec/sectorSize.x) * Constants.gridDimensions;
        if (ans.y + Constants.gridDimensions/2 < H) ans.y += Constants.gridDimensions/2;
        ans.x = (sec%sectorSize.x) * Constants.gridDimensions;
        if (ans.x + Constants.gridDimensions/2 < W) ans.x += Constants.gridDimensions/2;
    }
    
    void reportExplored(MapLocation loc) {
        int sec = getSector(loc);
        int inx = Constants.exploreStart+(sec/16);
        int g = rc.readSharedArray(inx);
        int val = 1&(g>>(inx%16));
        if (val == 0) {
            g += (1<<(inx%16));
            rc.writeSharedArray(inx, g);
        }
    }
    boolean isExplored(MapLocation loc) {
        int sec = getSector(loc);
        int inx = Constants.exploreStart+(sec/16);
        int g = rc.readSharedArray(inx);
        int val = 1&(g>>(inx%16));
        return val;
    }
    boolean isHostile(int sec) {
        int inx = Constants.hostileStart+(sec/16);
        int g = rc.readSharedArray(inx);
        int val = 1&(g>>(inx%16));
        return val;
    }
    void reportFlag(FlagInfo flag) {
        MapLocation loc = flag.location;
        if (flag.team = MyTeam) {
            int a = rc.readSharedArray(Constants.ourFlagsStart);
            int b = rc.readSharedArray(Constants.ourFlagsStart+1);
            int c = rc.readSharedArray(Constants.ourFlagsStart+2);
            int s = getSector(loc);
            if (a != s and b != s and c == 0) {
                rc.writeSharedArray(Constants.ourFlagsStart+1, s);
            }
            if (a != s and b == 0 and c == 0) {
                rc.writeSharedArray(Constants.ourFlagsStart+1, s);
            } 
            if (a == 0 and b == 0 and c == 0) {
                rc.writeSharedArray(Constants.ourFlagsStart, s);
            }
        } else {
            int a = rc.readSharedArray(Constants.theirFlagsStart);
            int b = rc.readSharedArray(Constants.theirFlagsStart+1);
            int c = rc.readSharedArray(Constants.theirFlagsStart+2);
            int s = getSector(loc);
            if (a != s and b != s and c == 0) {
                rc.writeSharedArray(Constants.theirFlagsStart+1, s);
            }
            if (a != s and b == 0 and c == 0) {
                rc.writeSharedArray(Constants.theirFlagsStart+1, s);
            } 
            if (a == 0 and b == 0 and c == 0) {
                rc.writeSharedArray(Constants.theirFlagsStart, s);
            }

        }
    }
    int distance(MapLocation a, MapLocation b) {
        return abs(a.x-b.x)+abs(a.y-b.y);
    }
}
