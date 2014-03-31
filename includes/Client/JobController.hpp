//
// JobController.hpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Wed Feb 12 13:06:04 2014 gautier lefebvre
//

#ifndef		__JOB_CONTROLLER_HPP__
#define		__JOB_CONTROLLER_HPP__

#include	<vector>
#include	"Protocol/Job.hpp"
#include	"Singleton.hpp"
#include	"Threading/Mutex.hpp"

#define		NB_FUNC		(21)
#define		NB_FUNC_GAME	(53)

namespace	GUI {
  class		Controller;
}

namespace	GUIG {
  class		Controller;
}

namespace	Client {
  class		JobController :public Singleton<Client::JobController> {
    friend class Singleton<Client::JobController>;

  private:
    Mutex	*_mutex;

    void	playerInfos(const Protocol::Job*, GUI::Controller *);
    void	playerStats(const Protocol::Job*, GUI::Controller *);
    void	newFriend(const Protocol::Job*, GUI::Controller *);
    void	loseFriend(const Protocol::Job*, GUI::Controller *);
    void	friendStatus(const Protocol::Job*, GUI::Controller *);
    void	groupRequest(const Protocol::Job*, GUI::Controller *);
    void	newPlayerInGroup(const Protocol::Job*, GUI::Controller *);
    void	playerLeftGroup(const Protocol::Job*, GUI::Controller *);
    void	groupLeader(const Protocol::Job*, GUI::Controller *);
    void	groupKicked(const Protocol::Job*, GUI::Controller *);
    void	groupDeleted(const Protocol::Job*, GUI::Controller *);
    void	groupMemberChangedRace(const Protocol::Job*, GUI::Controller *);
    void	recvWhisp(const Protocol::Job*, GUI::Controller *);
    void	recvMsgGroup(const Protocol::Job*, GUI::Controller *);
    void	fail(const Protocol::Job*, GUI::Controller *);
    void	success(const Protocol::Job*, GUI::Controller *);
    void	gameSearching(const Protocol::Job*, GUI::Controller *);
    void	endGameSearching(const Protocol::Job*, GUI::Controller *);
    void	newFriendRequest(const Protocol::Job*, GUI::Controller *);
    void	exit(const Protocol::Job*, GUI::Controller *);
    void	exitG(const Protocol::Job*, GUIG::Controller *);
    void	fileInfos(const Protocol::Job*, GUIG::Controller *);
    void	askFileExists(const Protocol::Job*, GUIG::Controller *);
    void	fileChunk(const Protocol::Job*, GUIG::Controller *);
    void	gameLoading(const Protocol::Job*, GUI::Controller *);
    void	gameLaunch(const Protocol::Job*, GUIG::Controller *);
    void	playerRoom(const Protocol::Job*, GUIG::Controller *);
    void	playerReady(const Protocol::Job*, GUIG::Controller *);
    void	changeDayNight(const Protocol::Job *, GUIG::Controller *);
    void	updateSpot(const Protocol::Job *, GUIG::Controller *);
    void	ressourceSpot(const Protocol::Job *, GUIG::Controller *);
    void	itemCreation(const Protocol::Job *, GUIG::Controller *);
    void	itemDestruction(const Protocol::Job *, GUIG::Controller *);
    void	updatingItem(const Protocol::Job *, GUIG::Controller *);
    void	objectKeepedByHero(const Protocol::Job *, GUIG::Controller *);
    void	objectPutByHero(const Protocol::Job *, GUIG::Controller *);
    void	objectPossessedByHero(const Protocol::Job *, GUIG::Controller *);
    void	waypointOfItem(const Protocol::Job *, GUIG::Controller *);
    void	itemMoving(const Protocol::Job *, GUIG::Controller *);
    void	stopingAction(const Protocol::Job *, GUIG::Controller *);
    void	itemAction(const Protocol::Job *, GUIG::Controller *);
    void	effectNotApplyOnItem(const Protocol::Job *, GUIG::Controller *);
    void	externEffectApplyOnItem(const Protocol::Job *, GUIG::Controller *);
    void	externEffectNotApplyOnItem(const Protocol::Job *, GUIG::Controller *);
    void	effectApplyOnItem(const Protocol::Job *, GUIG::Controller *);
    void	stanceOfUnit(const Protocol::Job *, GUIG::Controller *);
    void	unitHasBeenProduct(const Protocol::Job *, GUIG::Controller *);
    void	unitPutInProduction(const Protocol::Job *, GUIG::Controller *);
    void	unitHasBeenDeletedFromProductionList(const Protocol::Job *, GUIG::Controller *);
    void	buildingBuilt(const Protocol::Job *, GUIG::Controller *);
    void	unitStopBuilding(const Protocol::Job *, GUIG::Controller *);
    void	unitBuilding(const Protocol::Job *, GUIG::Controller *);
    void	unitMoveRessource(const Protocol::Job *, GUIG::Controller *);
    void	unitHarvest(const Protocol::Job *, GUIG::Controller *);
    void	unitEndStopingToHarvest(const Protocol::Job *, GUIG::Controller *);
    void	unitWaitToHarvest(const Protocol::Job *, GUIG::Controller *);
    void	unitStopHarvest(const Protocol::Job *, GUIG::Controller *);
    void	unitDeposit(const Protocol::Job *, GUIG::Controller *);
    void	playerAmelioration(const Protocol::Job *, GUIG::Controller *);
    void	ameliorationProduct(const Protocol::Job *, GUIG::Controller *);
    void	ameliorationDeletedFromProductionList(const Protocol::Job *, GUIG::Controller *);
    void	ping(const Protocol::Job *, GUIG::Controller *);
    void	playerRessources(const Protocol::Job *, GUIG::Controller *);
    void	itemAttackItem(const Protocol::Job *, GUIG::Controller *);
    void	itemAttackZone(const Protocol::Job *, GUIG::Controller *);
    void	itemUseCapacityOnZone(const Protocol::Job *, GUIG::Controller *);
    void	itemUseCapacityOnItem(const Protocol::Job *, GUIG::Controller *);
    void	capacityUsed(const Protocol::Job *, GUIG::Controller *);
    void	capacityOnAutoOrNot(const Protocol::Job *, GUIG::Controller *);
    void	youAre(const Protocol::Job *, GUIG::Controller *);
    void	player(const Protocol::Job *, GUIG::Controller *);
    void	recvWhispG(const Protocol::Job*, GUIG::Controller *);
    void	recvMsgGroupG(const Protocol::Job*, GUIG::Controller *);
    void	recvMsgGlob(const Protocol::Job*, GUIG::Controller *);


    struct commandFunc {
      Command::Command command;
      void	(JobController::*func)(const Protocol::Job*, GUI::Controller *);
    };

    const commandFunc jobFunc[NB_FUNC]={
      {Command::PINFOS, &JobController::playerInfos},
      {Command::PSTATS, &JobController::playerStats},
      {Command::GAMELOADING, &JobController::gameLoading},
      {Command::NFD, &JobController::newFriend},
      {Command::LFD, &JobController::loseFriend},
      {Command::SFD, &JobController::friendStatus},
      {Command::GR, &JobController::groupRequest},
      {Command::NPIG, &JobController::newPlayerInGroup},
      {Command::PLG, &JobController::playerLeftGroup},
      {Command::GPLD, &JobController::groupLeader},
      {Command::GRPKICKED, &JobController::groupKicked},
      {Command::GRPDELETED, &JobController::groupDeleted},
      {Command::GRPMBRCHGRACE, &JobController::groupMemberChangedRace},
      {Command::RWH, &JobController::recvWhisp},
      {Command::RMSGGRP, &JobController::recvMsgGroup},
      {Command::FAIL, &JobController::fail},
      {Command::SUCCESS, &JobController::success},
      {Command::GAMESEARCHING, &JobController::gameSearching},
      {Command::ENDGAMESEARCHING, &JobController::endGameSearching},
      {Command::NEWFRIENDREQUEST, &JobController::newFriendRequest},
      {Command::EXIT, &JobController::exit}
    };

    struct commandGameFunc {
      Command::Command command;
      void	(JobController::*func)(const Protocol::Job*, GUIG::Controller *);
    };

    const commandGameFunc jobGameFunc[NB_FUNC_GAME]={
      {Command::EXIT, &JobController::exitG},
      {Command::FINFOS, &JobController::fileInfos},
      {Command::RWH, &JobController::recvWhispG},
      {Command::RMSGGRP, &JobController::recvMsgGroupG},
      {Command::RMSGGLB, &JobController::recvMsgGlob},
      {Command::ASKFILEEXISTS, &JobController::askFileExists},
      {Command::FILECHUNK, &JobController::fileChunk},
      {Command::GAMELAUNCH, &JobController::gameLaunch},
      {Command::PLAYERINROOM, &JobController::playerRoom},
      {Command::PLAYERREADY, &JobController::playerReady},
      {Command::DAYNIGHT, &JobController::changeDayNight},
      {Command::UPDSPOT, &JobController::updateSpot},
      {Command::RESSSPOT, &JobController::ressourceSpot},
      {Command::OCREATE, &JobController::itemCreation},
      {Command::ODESTROY, &JobController::itemDestruction},
      {Command::OMAJ, &JobController::updatingItem},
      {Command::HPUOBJ, &JobController::objectKeepedByHero},
      {Command::HROBJ, &JobController::objectPutByHero},
      {Command::HPUOBJS, &JobController::objectPossessedByHero},
      {Command::OWP, &JobController::waypointOfItem},
      {Command::OMOVE, &JobController::itemMoving},
      {Command::OSTOP, &JobController::stopingAction},
      {Command::OACT, &JobController::itemAction},
      {Command::OSTOPEFFECT, &JobController::effectNotApplyOnItem},
      {Command::OTMPEFFECT, &JobController::externEffectApplyOnItem},
      {Command::OSTOPTMPEFFECT, &JobController::externEffectNotApplyOnItem},
      {Command::OEFFECT, &JobController::effectApplyOnItem},
      {Command::USTANCE, &JobController::stanceOfUnit},
      {Command::BPRODF, &JobController::unitHasBeenProduct},
      {Command::UPROD, &JobController::unitPutInProduction},
      {Command::UDPROD, &JobController::unitHasBeenDeletedFromProductionList},
      {Command::BBUILT, &JobController::buildingBuilt},
      {Command::USTOPBUILD, &JobController::unitStopBuilding},
      {Command::UBUILD, &JobController::unitBuilding},
      {Command::UPURESS, &JobController::unitMoveRessource},
      {Command::UHARVEST, &JobController::unitHarvest},
      {Command::USTOPWAITHARVEST, &JobController::unitEndStopingToHarvest},
      {Command::UWAITHARVEST, &JobController::unitWaitToHarvest},
      {Command::USTOPHARVEST, &JobController::unitStopHarvest},
      {Command::UDEPOSIT, &JobController::unitDeposit},
      {Command::PAMELIO, &JobController::playerAmelioration},
      {Command::PRODAMELIO, &JobController::ameliorationProduct},
      {Command::DAMELIO, &JobController::ameliorationDeletedFromProductionList},
      {Command::PING, &JobController::ping},
      {Command::PRESS, &JobController::playerRessources},
      {Command::OATTACK, &JobController::itemAttackItem},
      {Command::OZONEATTACK, &JobController::itemAttackZone},
      {Command::OUSEZONECAP, &JobController::itemUseCapacityOnZone},
      {Command::OUSECAP, &JobController::itemUseCapacityOnItem},
      {Command::OUSECAPA, &JobController::capacityUsed},
      {Command::OACTCAPA, &JobController::capacityOnAutoOrNot},
      {Command::PLAYER, &JobController::player},
      {Command::YOUARE, &JobController::youAre}
    };

  public:
    JobController();
    virtual ~JobController();

    void	doJob(Protocol::Job*, GUI::Controller*);
    void	doJobGame(Protocol::Job*, GUIG::Controller*);
  };
}

#endif
