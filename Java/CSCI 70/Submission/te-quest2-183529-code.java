package RAN;
import robocode.*;
import robocode.Robot;
import static robocode.util.Utils.normalRelativeAngleDegrees;

import java.util.Random;
import java.lang.Math;

/**
 * RAN - a robot by (your name here)
 */
public class RAN extends AdvancedRobot
{
	int countSearch = 0;
	double setGunTurnSpeed;
	String targetName;
	Random rand = new Random();
	double ctrToCnr;
	
	/**
	 * run: RAN's default behavior
	 */
	public void run() {
		targetName = null;
		setAdjustGunForRobotTurn(true);
		setGunTurnSpeed = 10;
		ctrToCnr = Math.sqrt(getBattleFieldHeight()*getBattleFieldHeight() + getBattleFieldWidth() * getBattleFieldWidth()) / 2;

		while (true) {
			turnGunRight(setGunTurnSpeed);
			countSearch++;
			if (countSearch > 2) {
				setGunTurnSpeed = -10;
			}
			if (countSearch > 5) {
				setGunTurnSpeed = 10;
			}
			if (countSearch > 11) {
				targetName = null;
			}
		}
	}

	public void onScannedRobot(ScannedRobotEvent e) {
		if (targetName != null && !e.getName().equals(targetName)) {
			return;
		}

		if (targetName == null) {
			targetName = e.getName();
		}

		countSearch = 0;

		if (e.getDistance() > ctrToCnr) {
			setGunTurnSpeed = normalRelativeAngleDegrees(e.getBearing() + (getHeading() - getRadarHeading()));

			turnGunRight(setGunTurnSpeed);
			turnRight(e.getBearing());
			setAhead((e.getDistance() - ctrToCnr)*2);
			setTurnRight(45);
			waitFor(new TurnCompleteCondition(this));
			return;
		}

		if (e.getDistance() > ctrToCnr/2) {
			fire(1);
		}		
		else {
			fire(3);
		}
		setGunTurnSpeed = normalRelativeAngleDegrees(e.getBearing() + (getHeading() - getRadarHeading()));
		turnGunRight(setGunTurnSpeed);

		if (e.getDistance() < 100) {
			if (e.getBearing() > -90 && e.getBearing() <= 90) {
				back(40);
			} else {
				ahead(40);
			}
		}
		scan();
	}

	public void onHitRobot(HitRobotEvent e) {
		targetName = e.getName();
		setGunTurnSpeed = normalRelativeAngleDegrees(e.getBearing() + (getHeading() - getRadarHeading()));
		turnGunRight(setGunTurnSpeed);
		fire(2);
	}
	
	public void onHitByBullet (HitByBulletEvent e)
	{
		if (targetName == e.getName()) {
			turnRight(90);
			ahead(rand.nextInt(250) - 150);
		}
		else {
			targetName = e.getName();
			setGunTurnSpeed = normalRelativeAngleDegrees(e.getBearing() + (getHeading() - getRadarHeading()));
			turnGunRight(setGunTurnSpeed);	
		}
	}
	
	public void onHitWall (HitWallEvent e) {
		ahead(-1*rand.nextInt(200));
	}
}
