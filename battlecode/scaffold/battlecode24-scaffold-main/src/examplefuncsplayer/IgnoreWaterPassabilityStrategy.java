package lib.Pathfinding.Passability;

import battlecode.common.GameActionException;
import battlecode.common.MapInfo;
import battlecode.common.MapLocation;
import battlecode.common.RobotController;

public class IgnoreWaterPassabilityStrategy implements PassabilityStrategy {

    @Override
    public boolean canPass(RobotController rc, MapLocation location) throws GameActionException {
        if (!rc.onTheMap(location)) {
            return false;
        }

        MapInfo mapInfo = rc.senseMapInfo(location);

        return mapInfo.isPassable() || mapInfo.isWater();
    }

}
