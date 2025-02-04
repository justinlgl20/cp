package bot1

import battlecode.common.*;

public abstract class Robot {
    static RobotController rc;
    static int H, W;
    static int turnCount = 1;
    
    static Team myTeam;
    static Team oppTeam;

    static RobotInfo[] myRobots;
    static RobotInfo[] oppRobots;

    static int MAP_TYPE = 1;

    static Comms comm;

    static PathFinder pathfinder;

    static final int SMALL = 0, MEDIUM=1, LARGE=2;

    void checkMapSize() {
        if (H*W < 1000) MAP_TYPE = SMALL;
    }
    public Robot(RobotController rc) throws GameActionException{
        this.rc = rc;
        H = rc.getMapHeight();
        W = rc.getMapWidth();
        myTeam = rc.getTeam();
        oppTeam = rc.getTeam().opponent();
        Comms.init(rc);
        checkMapSize();
        turnCount++;
    }

    abstract void play() throws GameActionException;

    void initTurn() throws GameActionException {
        myRobots = rc.senseNearbyRobots(-1, myTeam);
        oppRobots = rc.senseNearbyRobots(-1, oppTeam);
        if (turnCount % 130 == 0) comm.reset();
        for (robotInfo enemy : oppRobots) {
            comm.reportHostile(enemy);
        }
        for (FlagInfo flag : rc.senseNearbyFlags(-1)) {
            comm.reportFlag(flag);
        }


    }

    void endTurn() throws GameActionException {}

}
