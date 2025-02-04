package lib.Pathfinding.Passability;

import battlecode.common.GameActionException;
import battlecode.common.MapLocation;
import battlecode.common.RobotController;

public class RobotBlockPassabilityStrategy implements PassabilityStrategy {

    @Override
    public boolean canPass(RobotController rc, MapLocation location) throws GameActionException {
        return rc.onTheMap(location) && rc.sensePassability(location) && !rc.canSenseRobotAtLocation(location);
    }

}
