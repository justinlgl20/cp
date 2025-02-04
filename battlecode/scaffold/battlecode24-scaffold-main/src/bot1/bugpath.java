package bot1;

import battlecode.common.*;

public class BugPath {
    RobotController rc;

    static int H, W;

    BugPath() {
        this.rc = Robot.rc;
        H = Robot.H;
        W = Robot.W;
        states = new int[W][];
    }

    int bugPathIndex = 0;

    int stateIndex = 0;

    boolean isReady() {
        return stateIndex >= W;
    }

    void fill() {
        while (stateIndex < W) {
            if (Clock.getBytecodesLeft() < 1000) return;
            states[stateIndex++] = new int[H];
        }
    }
    Boolean rotateRight = null;

    MapLocation lastObstacleFound=null;

    MapLocation lastCurrent = null;
    int minDistToTarget = Constants.INF;
    MapLocation minLocationToTarget = null;
    MapLocation prevTarget = null;
    Direction[] dirs = Direction.values();

    int[][] states;

    MapLocation myLoc;
    boolean[] canMoveArray;
    int round;

}
