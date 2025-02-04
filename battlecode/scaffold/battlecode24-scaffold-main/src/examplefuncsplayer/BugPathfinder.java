package lib.Pathfinding;

import lib.Pathfinding.Passability.RobotBlockPassabilityStrategy;
import battlecode.common.Direction;
import battlecode.common.GameActionException;
import battlecode.common.MapLocation;
import battlecode.common.RobotController;
import lib.Pathfinding.Passability.PassabilityStrategy;

public class BugPathfinder extends Pathfinder {

    private MapLocation targetLocation;
    private MapLocation startLocation;
    private Direction currentDirection;
    private boolean goalSide = false;

    public BugPathfinder(RobotController rc) {
        super(rc);
        this.defaultPassabilityStrategy = new RobotBlockPassabilityStrategy();
    }
    public BugPathfinder(RobotController rc, PassabilityStrategy defaultPassabilityStrategy) {
        super(rc, defaultPassabilityStrategy);
    }

    @Override
    public MapLocation getBestAdjacentLocation(MapLocation currentLocation, MapLocation target, PassabilityStrategy passabilityStrategy) throws GameActionException {
        if (!target.equals(this.targetLocation)) {
            setNewTarget(currentLocation, target);
        }

        if (target.equals(currentLocation)) {
            return currentLocation;
        }

        Direction targetDirection = currentLocation.directionTo(targetLocation);
        MapLocation adjacentLocation = rc.adjacentLocation(targetDirection);

        if (currentDirection == null && rc.canSenseLocation(adjacentLocation) && passabilityStrategy.canPass(rc, adjacentLocation)) {
            return adjacentLocation;
        }
        else {
            if (currentDirection == null) {
                currentDirection = targetDirection;
                goalSide = !isLeft(startLocation, targetLocation, currentLocation);
            }

            if (goalSide == isLeft(startLocation, targetLocation, currentLocation)) {
                currentDirection = null;
                return null;
            }

            for (int i = 0; i < 8; i++) {
                MapLocation followWallLocation = rc.adjacentLocation(currentDirection);

                if (passabilityStrategy.canPass(rc, followWallLocation)) {
                    currentDirection = currentDirection.rotateRight();
                    return followWallLocation;
                }
                else {
                    currentDirection = currentDirection.rotateLeft();
                }
            }
        }

        return null;
    }

    public boolean isLeft(MapLocation lineStart, MapLocation lineEnd, MapLocation point) {
        return ((lineEnd.x - lineStart.x)*(point.y - lineStart.y) - (lineEnd.y - lineStart.y)*(point.x - lineStart.x)) > 0;
    }

    public void setNewTarget(MapLocation startLocation, MapLocation targetLocation) {
        this.currentDirection = null;
        this.targetLocation = targetLocation;
        this.startLocation = startLocation;
    }

}