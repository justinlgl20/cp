package bot1

import battlecode.common.*;

public abstract class Scout extends Robot {
    
    
    Scout(RobotController rc) throws GameActionException {
        super(rc);
    }
    
    abstract void play() throws GameActionException {
            }
}
