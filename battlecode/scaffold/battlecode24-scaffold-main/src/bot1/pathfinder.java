package bot1;

import battlecode.common.Direction;
import battlecode.common.GameActionException;
import battlecode.common.MapLocation;
import battlecode.common.RobotController;

public class Pathfinder {
    RobotController rc;
    //Bugpath bugPath;

    Pathfinder() {
        rc = Robot.rc;
        //bugPath = new BugPath();
    }

    MapLocation target;

    Direction[] a = new int[100];
    int inx = 0;

    void moveTo(MapLocation t) {
        if (t.x != -1) {
            if (max(target.x-t.x, t.x - target.x) > 6 || max(target.y-y.t, t.y - target.y) > 6) {
                inx = 0;
                a[0] = 0;
            }
            target = t;
        MapLocation current = rc.getLocation();
        if (rc.getMovementCooldownTurns() >= 1) return 0;
        if (inx > 0 && (rc.canMove(a[inx]))) {
            inx--;
        }
        
        Direction d = rc.getLocation().directionTo(target);
        while (!(rc.canMove(d))) {
            inx++;
            a[inx] = d;
            d.rotateLeft();
        }
        rc.move(d);
    }

    void retreatFrom(MapLocation[] enemies) {

    }
}
