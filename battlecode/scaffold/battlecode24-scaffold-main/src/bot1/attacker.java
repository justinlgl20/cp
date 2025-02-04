package bot1

import battlecode.common.*;

public abstract class Attacker extends Robot {

    boolean chicken = false;
    
    
    Attacker(RobotController rc) throws GameActionException {
        super(rc);
    }
    
    abstract void play() throws GameActionException {

    }

    class AttackTarget {
        RobotInfo x;
        boolean attacker = false;

        boolean isBetterThan(AttackTarget t) {
            if (t == null) return true;
            if (t.x.hasFlag() return false;
            if (attacker & !t.attacker) return true;
            if (!attacker & t.attacker) return false;
            return x.health <= t.x.health;
        }

        AttackTarget(RobotInfo r) {
            x = r;
            if (x.attackLevel >= max(1, (turnCount/700))) {
                attacker = true;
            }
        }
    }
    
    AttackTarget getBestTarget(int onlyAttackers) {
        if (!rc.isActionReady()) return;
        AttackTarget bestTarget = null;
        for (RobotInfo i : oppRobots) {
            AttackTarget g = new AttackTarget(i);
            if (onlyAttackers && !g.attacker) continue;
            if (rc.canAttack(i.location)) {
                if (g.isBetterThan(bestTarget)) bestTarget = g;
            }
        }
        return bestTarget;
    }
    class HealTarget {
        RobotInfo x;
        boolean attacker = false;

        boolean isBetterThan(HealTarget t) {
            if (t == null) return true;
            if (t.hasFlag()) return false;
            if (t.attacker && !attacker) return false;
            if (!t.attacker && attacker) return true;
            return x.health <= t.x.health;
        }
    }
    void moveToTarget(MapLocation target) {
        pathfinder.moveTo(target);
    }
    void attack() { // should probably keep track of targets which we move out of sight of
        AttackTarget target = getBestTarget();
        boolean attacking = true;
        if (target == null) {
            attacking = false;
            // go to a hostile sector nearby
            int dist = 1e9;
            MapLocation tar = null;
            for (int i = 0; i < comm.numSectors; i++) {
                if (comm.isHostile(i) && distance(rc.getLocation(), getSectorCentre(i)) <= dist) {
                    dist = distance(rc.getLocation(), getSectorCentre(i));
                    tar = getSectorCentre(i);
                }
            }
            moveTo(tar);
        }

        // analyse what we need most


        if (attacking && chicken == false && rc.canAttack(target.location)) {
            rc.attack(target.location);
            //move back and to the side now
            pathfinder.retreatFrom(oppTeam);
        } else if (chicken == false && !rc.canAttack(target.location)) {
            pathfinder.moveTo(target.location);
        }
        if (chicken == true or !rc.canAttack(target.location)){
            // now try to heal them if we can't attack or we're in chicken mode
            RobotInfo tar = null;
            HealTarget target = null;
        }
        // build a trap if most are chickening and there aren't traps covering retreat

    }
}
