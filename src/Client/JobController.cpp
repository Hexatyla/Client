//
// JobController.cpp for pfa in /home/gautier/Projets/pfa
// 
// Made by gautier lefebvre
// Login   <lefebv_n@epitech.net>
// 
// Started on  Wed Feb 12 13:26:18 2014 gautier lefebvre
// Last update Fri Mar 21 17:46:06 2014 gautier lefebvre
//

#include	<cstring>
#include	"Client/JobController.hpp"
#include	"Protocol/Job.hpp"
#include	"Factory/Protocol.hpp"
#include	"GUI/Controller.hpp"
#include	"GUIG/Controller.hpp"
#include	"Threading/ScopeLock.hpp"
#include	"Protocol/JobResolver.hpp"
#include	"Logger.hpp"

#define		LOCK_JOBCONTROLLER	ScopeLock s(this->_mutex)

#define MUST_IMPLEMENT	{ std::string fffffff = __PRETTY_FUNCTION__; Logger::getInstance()->logf("Must implement %s", Logger::FATAL, &fffffff); }

Client::JobController::JobController():
  _mutex(new Mutex())
{}

Client::JobController::~JobController() {}

void		Client::JobController::doJob(Protocol::Job* job, GUI::Controller *c) {
  LOCK_JOBCONTROLLER;
  bool good = false;
  if (job) {
    std::cout << *job << std::endl;
    for (int i = 0 ; i < NB_FUNC ; ++i) {
      if (job->getCommand() == this->jobFunc[i].command) {
	(this->*jobFunc[i].func)(job, c);
	Logger::getInstance()->logf("Found job %j", Logger::INFORMATION, job);
	good = true;
	break;
      }
    }
    if (!good) {
      Logger::getInstance()->logf("Did not find job %j", Logger::FATAL, job);
    }
    Factory::Protocol::Job::remove(job);
  }
}

void		Client::JobController::doJobGame(Protocol::Job* job, GUIG::Controller *c) {
  LOCK_JOBCONTROLLER;
  bool good = false;
  if (job) {
    std::cout << *job << std::endl;
    for (int i = 0 ; i < NB_FUNC_GAME ; ++i) {
      if (job->getCommand() == this->jobGameFunc[i].command) {
	(this->*jobGameFunc[i].func)(job, c);
	Logger::getInstance()->logf("Found job %j", Logger::INFORMATION, job);
	good = true;
	break;
      }
    }
    if (!good) {
      Logger::getInstance()->logf("Did not find job %j", Logger::FATAL, job);
    }
    Factory::Protocol::Job::remove(job);
  }
}

void		Client::JobController::playerInfos(const Protocol::Job *job, GUI::Controller *) {
  /* donne les informations du client */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick(args[0].pseudo);
  std::string	mail(args[1].mail);
  std::string	avatar(args[2].avatar);
  ::User::Status status = args[3].userStatus;

  (void)nick;
  (void)mail;
  (void)avatar;
  (void)status;
}

void		Client::JobController::playerStats(const Protocol::Job *job, GUI::Controller *) {
  /* donne les stats du client */
  const Protocol::Argument *args = job->getArguments();
  unsigned int	wx = args[0].stat; // win race X
  unsigned int	lx = args[1].stat; // lose race X
  unsigned int	wy = args[2].stat; // win race Y
  unsigned int	ly = args[3].stat; // ...
  unsigned int	wz = args[4].stat;
  unsigned int	lz = args[5].stat;

  (void)wx;
  (void)lx;
  (void)wy;
  (void)ly;
  (void)wz;
  (void)lz;
}

void		Client::JobController::newFriend(const Protocol::Job *job, GUI::Controller *controller) {
  /* tu as un nouvel ami, donne son nick et son status */
  /* job envoyé à la connexion pour donner la liste d'amis */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;
  ::User::Status status = args[1].userStatus;

  controller->friends_receiveAddFriend(nick, status);
}

void		Client::JobController::loseFriend(const Protocol::Job *job, GUI::Controller *controller) {
  /* tu as perdu un ami, donne son nick */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;

  controller->friends_receiveDeleteFriend(nick);
}

void		Client::JobController::friendStatus(const Protocol::Job *job, GUI::Controller *controller) {
  /* un ami a changé de status, donne son nick et son status */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;
  ::User::Status status = args[1].userStatus;

  controller->friends_receiveAddFriend(nick, status);
}

void		Client::JobController::newFriendRequest(const Protocol::Job *job, GUI::Controller *controller) {
  /* un joueur vous a envoyé une demande d'ami, donne son nick
   Job envoyé à la connexion pour donner les requetes en attente */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;

  controller->friends_receiveRequestFriend(nick);
}

void		Client::JobController::groupRequest(const Protocol::Job *job, GUI::Controller *c) {
  /* tu as été invité à rejoindre un groupe
   donne le nick du joueur qui a invité */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;

  c->group_receiveRequestGroup(nick);
}

void		Client::JobController::newPlayerInGroup(const Protocol::Job *job, GUI::Controller *c) {
  /* nouveau joueur dans le groupe, donne son nick et sa race */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;
  Race::Race	race = args[1].race;

  c->group_receiveNewMemberGroup(nick, race);
}

void		Client::JobController::playerLeftGroup(const Protocol::Job *job, GUI::Controller *ctrl) {
  /* un joueur a quitté le groupe, donne son nick */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;

  ctrl->group_receiveLeftPlayer(nick);
}

void		Client::JobController::groupLeader(const Protocol::Job *job, GUI::Controller *c) {
  /* donne le nick du chef de groupe
   envoyé à la création du groupe et quand un nouveau joueur rejoint le groupe */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;

  c->core_receiveCreatingGroupValidate(nick);
}

void		Client::JobController::groupKicked(const Protocol::Job *, GUI::Controller *c) {
  /* tu as été kické du groupe (pas d'arguments) */
  c->group_closeGroup("");
}

void		Client::JobController::groupDeleted(const Protocol::Job *, GUI::Controller *c) {
  /* ton groupe a été supprimé (pas d'arguments) */
  c->group_closeGroup("");
}

void		Client::JobController::groupMemberChangedRace(const Protocol::Job *job, GUI::Controller *c) {
  /* un joueur du groupe a changé de race, donne son nick et sa race */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;
  Race::Race	race = args[1].race;

  c->group_receiveMemberChangedRace(nick, race);
}

void		Client::JobController::recvWhisp(const Protocol::Job *job, GUI::Controller *c) {
  /* tu as reçu un message privé, donne le nick de l'expéditeur et le message reçu */
  const Protocol::Argument *args = job->getArguments();
  std::string	from = args[0].pseudo;
  std::string	to = args[1].pseudo;
  std::string	msg = args[2].msg;

  c->convers_receiveMessage(to, from, msg);
}

void		Client::JobController::recvMsgGroup(const Protocol::Job *job, GUI::Controller *c) {
  /* tu as reçu un message envoyé par un membre du group, donne le nick de l'expéditeur et le message */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;
  std::string	msg = args[1].msg;

  c->group_receiveMessage(nick, msg);
}

void		Client::JobController::recvWhispG(const Protocol::Job *job, GUIG::Controller *c) {
  /* tu as reçu un message privé, donne le nick de l'expéditeur et le message reçu */
  const Protocol::Argument *args = job->getArguments();
  std::string	from = args[0].pseudo;
  std::string	to = args[1].pseudo;
  std::string	msg = args[2].msg;

  c->guigChatbox_recvWhisp(from, msg);
}

void		Client::JobController::recvMsgGroupG(const Protocol::Job *job, GUIG::Controller *c) {
  /* tu as reçu un message envoyé par un membre du group, donne le nick de l'expéditeur et le message */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;
  std::string	msg = args[1].msg;

  c->guigChatbox_recvGrpMsg(nick, msg);
}

void		Client::JobController::recvMsgGlob(const Protocol::Job *job, GUIG::Controller *c) {
  /* tu as reçu un message privé, donne le nick de l'expéditeur et le message reçu */
  const Protocol::Argument *args = job->getArguments();
  std::string	from = args[0].pseudo;
  std::string	msg = args[1].msg;

  c->guigChatbox_recvMsgGlob(from, msg);
}

void		Client::JobController::success(const Protocol::Job *job, GUI::Controller *c) {
  /* success command, donne la commande
   envoyé à la connexion ou à l'inscription */
  const Protocol::Argument *args = job->getArguments();
  Command::Command	command = args[0].command;

  if (command == Command::CO)
  {
    c->signinup_INsuccessfull("");
  }
  else if (command == Command::REG)
  {
    c->signinup_UPsuccessfull("");
  }
}

void		Client::JobController::fail(const Protocol::Job *job, GUI::Controller *c) {
  /* une command a fail, donne la commande et l'erreur */
  const Protocol::Argument *args = job->getArguments();
  Command::Command	command = args[0].command;
  Error::Code		code = args[1].error;
  std::string		errorString = Error::CodeToString(code);

  if (command == Command::CO)
  {
    c->signinup_INerror("");
  }
  else if (command == Command::REG)
  {
    c->signinup_UPerror("");
  }
  (void)code;
}

void		Client::JobController::gameSearching(const Protocol::Job *, GUI::Controller *c) {
  /* tu es en attente de trouver des joueurs pour jouer */

  c->core_receiveStartGame("");
}

void		Client::JobController::endGameSearching(const Protocol::Job *, GUI::Controller *c) {
  /* tu as été sorti de la file d'attente (jeu trouvé, ou groupe delete, ou membre du groupe déconnecté) */

  c->core_receiveStopGame("");
}

void		Client::JobController::exit(const Protocol::Job *, GUI::Controller *c) {
  /* connexion avec le serveur perdue */

  c->core_back("");
}

void		Client::JobController::exitG(const Protocol::Job *, GUIG::Controller *c) {
  /* connexion avec le serveur perdue (avec GUIG) */

  // c->core_back("");
}

void		Client::JobController::fileInfos(const Protocol::Job *job, GUIG::Controller *) {
  /* envoie les informations du fichier, le nom du fichier, sa taille et le nombre de parties du fichier que le serveur va envoyer */
  const Protocol::Argument *args = job->getArguments();
  std::string	filename = args[0].filename;
  unsigned long long size = args[1].filesize;
  unsigned int	nb_chunk = args[2].nb_chunk;

  (void)filename;
  (void)size;
  (void)nb_chunk;
}

void		Client::JobController::askFileExists(const Protocol::Job *job, GUIG::Controller *c) {
  /* le serveur demande si le fichier existe coté client */
  const Protocol::Argument *args = job->getArguments();
  std::string filename = args[0].filename;

  std::cout << "ij" << std::endl;
  c->progress_receiveFileExist(filename);
  std::cout << "ij" << std::endl;
}

void		Client::JobController::fileChunk(const Protocol::Job *job, GUIG::Controller *) {
  /* partie d'un fichier, donne le nom du fichier, le numero de la partie et la partie */
  const Protocol::Argument *args = job->getArguments();
  std::string	filename = args[0].filename;
  unsigned int	id_chunk = args[1].id_chunk;
  int		size_chunk = args[2].size_chunk;
  char		chunk[1025];

  chunk[size_chunk] = '\0';
  memcpy(chunk, args[3].filechunk, size_chunk);
  (void)filename;
  (void)id_chunk;
  (void)size_chunk;
  (void)chunk;
}

void		Client::JobController::gameLoading(const Protocol::Job *, GUI::Controller *c) {
  /* annonce le chargement d'une partie avant d'envoyer fichier toussa toussa */

  c->core_gameLoading("");
}

void		Client::JobController::gameLaunch(const Protocol::Job *, GUIG::Controller *c) {
  /* annonce lancement de la partie */

  c->endLoading();
}

void		Client::JobController::playerRoom(const Protocol::Job *job, GUIG::Controller *c) {
  /* nouveau joueur dans la room, donne son nick, sa race et dit s'il est ready
   Job envoyé pour chaque joueur une fois que la room est prête */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;
  Race::Race	race = args[1].race;
  int		team = args[2].team;
  bool		ready = args[3].yes;

  c->progress_receivePlayerInRoom(nick, team, race, ready);
}

void		Client::JobController::playerReady(const Protocol::Job *job, GUIG::Controller *c) {
  /* un joueur de la room est pret, donne son nick */
  const Protocol::Argument *args = job->getArguments();
  std::string	nick = args[0].pseudo;

  c->progress_receiveReadyPlayer(nick);
}

void		Client::JobController::changeDayNight(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce le changement jour/nuit */
  bool day; /* TRUE si c'est le jour, FALSE si c'est la nuit */
  Protocol::JobResolver::getInstance()->dayNightSwitch(job, day);
  c->game_changeDayNight(day);
}

void		Client::JobController::updateSpot(const Protocol::Job *job, GUIG::Controller *c) {
  /* Mise à jour d'un spot */
  Kernel::ID::id_t id;
  unsigned int amount;
  Protocol::JobResolver::getInstance()->updateSpot(job, id, amount);
  c->game_updateSpot(id, amount);
}

void		Client::JobController::ressourceSpot(const Protocol::Job *job, GUIG::Controller *c) {
  /* Création d'un spot de ressources */
  Kernel::ID::id_t id;
  double x, y, z;
  Game::Ressources::Type type;
  unsigned int amount;
  Protocol::JobResolver::getInstance()->ressourceSpot(job, id, x, y, z, type, amount);
  c->game_createSpot(id, x, y, z, type, amount);
}

void		Client::JobController::itemCreation(const Protocol::Job *job, GUIG::Controller *c) {
  /* Création d'un item */
  Kernel::Serial serial;
  Kernel::ID::id_t id;
  double x, y, z;
  int orientation;
  Kernel::ID::id_t ownerID;
  Protocol::JobResolver::getInstance()->createItem(job, serial, id, x, y, z, orientation, ownerID);
  /* type = Kernel::Manager::getInstance()->getData(serial)->type ; Factory::Game::XXX::create(...) */
  c->game_itemCreation(serial, id, x, y, z, orientation, ownerID);
}

void		Client::JobController::itemDestruction(const Protocol::Job *job, GUIG::Controller *c) {
  /* Destruction d'un item */
  Kernel::ID::id_t id;
  Protocol::JobResolver::getInstance()->deleteItem(job, id);
  /* type = item->getType() ; Factory::Game::XXX::remove() */

  c->game_itemDestruction(id);
}

void		Client::JobController::updatingItem(const Protocol::Job *job, GUIG::Controller *c) {
  /* Mise à jour d'un item */
  Kernel::ID::id_t id;
  double x, y, z; /* if dynamic_cast<Game::Movable *>(item) { setX; setY; setZ; } */
  int orientation; /* if dynamic_cast<Game::Movable *>(item) { setOrientation } */
  unsigned int life, ress; /* Game::AElement::setLife ; Game::AElement::setRessource; */
  unsigned int xp, level; /* Game::AElement::setXP ; Game::AElement::setLevel ; */
  Protocol::JobResolver::getInstance()->updateItem(job, id, x, y, z, orientation, life, ress, xp, level);

  c->game_itemUpdate(id, x, y, z, orientation, life, ress, xp, level);
}

void		Client::JobController::objectKeepedByHero(const Protocol::Job *job, GUIG::Controller *c) {
  /* Un héros a récupérer un item */
  /* Game::Hero::addObject */
  Kernel::ID::id_t idHero, idObject;
  Protocol::JobResolver::getInstance()->heroPickedUpAnObject(job, idHero, idObject);

  c->game_objectKeepedByHero(idHero, idObject);
}

void		Client::JobController::objectPutByHero(const Protocol::Job *job, GUIG::Controller *c) {
  /* Un héros a déposé un objet */
  /* Game::Hero::removeObject */
  Kernel::ID::id_t idHero, idObject;
  Protocol::JobResolver::getInstance()->heroReleasedObject(job, idHero, idObject);

  c->game_objectPutByHero(idHero, idObject);
}

void		Client::JobController::objectPossessedByHero(const Protocol::Job *job, GUIG::Controller *c) {
  /* Liste des objets possédés par un héros */
  Kernel::ID::id_t idHero;
  std::vector<Kernel::ID::id_t> objects;
  Protocol::JobResolver::getInstance()->heroObjectsList(job, idHero, objects);

  c->game_objectPossessedByHero(idHero, objects);
}

void		Client::JobController::waypointOfItem(const Protocol::Job *job, GUIG::Controller *c) {
  /* Waypoint en cours d'un objet */
  Kernel::ID::id_t id;
  double x, y, z, speed;
  unsigned int wpID;
  Protocol::JobResolver::getInstance()->itemWaypoint(job, id, wpID, x, y, z, speed);
  /* item->setWaypoints(std::vector<Vector3d>(1, Vector3d(x, y, z)); item->setSpeed(speed); */
  c->game_waypointOfItem(id, x, y, z, speed, wpID);
}

void		Client::JobController::itemMoving(const Protocol::Job *job, GUIG::Controller *c) {
  /* Un item bouge */
  Kernel::ID::id_t id;
  double x, y, z;
  Protocol::JobResolver::getInstance()->itemMove(job, id, x, y, z);
  /* action = Factory::Game::Action::create(Game::ACTION_MOVE);
     action->move.x/y/z = x/y/z;
     item->setAction(action); */
  c->game_itemMoving(id, x, y, z);
}

void		Client::JobController::stopingAction(const Protocol::Job *job, GUIG::Controller *c) {
  /* Arrête l'action d'un item */
  Kernel::ID::id_t id;
  Protocol::JobResolver::getInstance()->itemStopAction(job, id);
  /* item->stopAction() ; */

  c->game_stopingAction(id);
}

void		Client::JobController::itemAction(const Protocol::Job *job, GUIG::Controller *c) {
  /* Définit l'action d'un item */
  Kernel::ID::id_t id;
  Game::eAction act;
  Protocol::JobResolver::getInstance()->itemAction(job, id, act);
  /* action = Factory::Game::Action::create(act);
     item->setAction(action)
  */
  c->game_itemAction(id, act);
}

void		Client::JobController::effectNotApplyOnItem(const Protocol::Job *job, GUIG::Controller *c) {
  /* Un effet n'est plus appliqué sur un item */
  Kernel::ID::id_t id;
  Kernel::Serial effect;
  Protocol::JobResolver::getInstance()->stopItemEffect(job, id, effect);
  /*  item->removeEffect(effect); */
  c->game_effectNotApplyOnItem(id, effect);
}

void		Client::JobController::externEffectApplyOnItem(const Protocol::Job *job, GUIG::Controller *c) {
  /* Un effet externe est appliqué à un item -> un effet qui ne vient pas de lui (ex. : aura) */
  Kernel::ID::id_t idItem, idEffectOwner;
  Kernel::Serial effect;
  Protocol::JobResolver::getInstance()->temporaryEffect(job, idItem, effect, idEffectOwner);
  /* Game::AElement::getEffects() sur effectOwner, récupérer effet avec le bon serial
     Game::AElement::addEffect(Game::Effect *);
   */
  c->game_externEffectApplyOnItem(idItem, idEffectOwner, effect);
}

void		Client::JobController::externEffectNotApplyOnItem(const Protocol::Job *job, GUIG::Controller *c) {
  /* Un effet externe n'est plus appliqué à un item */
  Kernel::ID::id_t idItem, idEffectOwner;
  Kernel::Serial effect;
  Protocol::JobResolver::getInstance()->removeTemporaryEffect(job, idItem, effect, idEffectOwner);
  /* Game::AElement::getEffects() sur effectOwner, récupérer effet avec le bon serial
     Game::AElement::removeEffect(Game::Effect *);
   */
  c->game_externEffectNotApplyOnItem(idItem, idEffectOwner, effect);
}

void		Client::JobController::effectApplyOnItem(const Protocol::Job *job, GUIG::Controller *c) {
  /* Un effet est appliqué à un item */
  Kernel::ID::id_t id;
  Kernel::Serial serial;
  double percentage;
  Protocol::JobResolver::getInstance()->itemEffect(job, id, serial, percentage);
  /* Game::AElement::addEffect(serial) */

  c->game_effectApplyOnItem(id, serial, percentage);
}

void		Client::JobController::stanceOfUnit(const Protocol::Job *job, GUIG::Controller *c)
{
  /* Stance d'une unité */
  Kernel::ID::id_t id;
  Game::Stance::Type stance;
  Protocol::JobResolver::getInstance()->unitStance(job, id, stance);
  /* Game::Unit::setStance(stance); */

  c->game_stanceOfUnit(id, stance);
}

void		Client::JobController::unitHasBeenProduct(const Protocol::Job *job, GUIG::Controller *c) {
  /* Une unité a été produite par un batiment */
  Kernel::ID::id_t building;
  Kernel::Serial unit;
  Protocol::JobResolver::getInstance()->unitHasBeenProduced(job, building, unit);

  c->game_unitHasBeenProduct(building, unit);
}

void		Client::JobController::unitPutInProduction(const Protocol::Job *job, GUIG::Controller *c)
{
  /* Une unité a été mise en production */
  Kernel::ID::id_t building;
  Kernel::Serial unit;
  unsigned int queueID;
  Protocol::JobResolver::getInstance()->unitProduction(job, building, queueID, unit);

  c->game_unitPutInProduction(building, unit, queueID);
}

void		Client::JobController::unitHasBeenDeletedFromProductionList(const Protocol::Job *job, GUIG::Controller *c)
{
  /* Une unité a été supprimée de la liste de production */
  Kernel::ID::id_t building;
  Kernel::Serial unit;
  Protocol::JobResolver::getInstance()->removeUnitFromProduction(job, building, unit);
  /* building->removeFromQueue(unit); */

  c->game_unitHasBeenDeletedFromProductionList(building, unit);
}

void		Client::JobController::buildingBuilt(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'un building a été construit (-> on peut produire des unités en utilisant celui-ci */
  Kernel::ID::id_t id;
  Protocol::JobResolver::getInstance()->buildingHasBeenBuilt(job, id);
  /* building->setBuilt(true) */

  c->game_buildingBuilt(id);
}

void		Client::JobController::unitStopBuilding(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'une unité arrête de construire un bâtiment */
  Kernel::ID::id_t unit, building;
  Protocol::JobResolver::getInstance()->unitStopBuildingBuilding(job, unit, building);
  /* building->removeBuilder(unit); */

  c->game_unitStopBuilding(unit, building);
}

void		Client::JobController::unitBuilding(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'une unité construit un bâtiment */
  Kernel::ID::id_t unit, building;
  Protocol::JobResolver::getInstance()->unitCreateBuilding(job, unit, building);
  /* building->addBuilder(unit); */

  c->game_unitBuilding(unit, building);
}

void		Client::JobController::unitMoveRessource(const Protocol::Job *job, GUIG::Controller *c) {
  /* Donne les ressources transportées par une unité */
  Kernel::ID::id_t unit;
  unsigned int gold, wood, food;
  Protocol::JobResolver::getInstance()->unitPickingUpRessources(job, unit, gold, wood, food);
  /* unit->setRessources(Game::Ressources::WOOD, wood)... */

  c->game_unitMoveRessource(unit, gold, wood, food);
}

void		Client::JobController::unitHarvest(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'une unité est en train de récolter un spot de ressources */
  Kernel::ID::id_t unit, spot;
  Protocol::JobResolver::getInstance()->unitHarvest(job, unit, spot);
  /* spot->addHarveter(unit); */

  c->game_unitHarvest(unit, spot);
}

void		Client::JobController::unitEndStopingToHarvest(const Protocol::Job *job, GUIG::Controller *c)
{
  /* Annonce qu'une unité a arrêté d'attendre pour récolter */
  Kernel::ID::id_t unit;
  Protocol::JobResolver::getInstance()->unitStopWaitHarvest(job, unit);

  c->game_unitEndStopingToHarvest(unit);
}

void		Client::JobController::unitWaitToHarvest(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'une unité attends pour récolter */
  Kernel::ID::id_t unit;
  Protocol::JobResolver::getInstance()->unitWaitHarvest(job, unit);

  c->game_unitWaitToHarvest(unit);
}

void		Client::JobController::unitStopHarvest(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'une unité arrête de récolter */
  Kernel::ID::id_t unit;
  Protocol::JobResolver::getInstance()->unitStopHarvest(job, unit);

  c->game_unitStopHarvest(unit);
}

void		Client::JobController::unitDeposit(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'une unité dépose ses ressources dans un batiment */
  Kernel::ID::id_t unit, building;
  Protocol::JobResolver::getInstance()->unitDeposit(job, unit, building);
  /* pas sur qu'il faille faire qqchose, c'est plus question design, jjouer un son ou quoi ... */
  c->game_unitDeposit(unit, building);
}

void		Client::JobController::playerAmelioration(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'un joueur a une amelioration */
  Kernel::ID::id_t playerID;
  Kernel::Serial type, amelioration;
  Protocol::JobResolver::getInstance()->playerHasAmelioration(job, playerID, type, amelioration);
  /* TODO : Add function in Game::Player */
  c->game_playerAmelioration(playerID, type, amelioration);
}

void		Client::JobController::ameliorationProduct(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'un joueur a mis en production une amélioration */
  Kernel::ID::id_t playerID;
  Kernel::Serial type, amelioration;
  unsigned int qID;
  Protocol::JobResolver::getInstance()->ameliorationProduction(job, playerID, type, amelioration, qID);
  /* player->insertInQueue(type, amelioration, qID); */

  c->game_ameliorationProduct(playerID, type, amelioration, qID);
}

void		Client::JobController::ameliorationDeletedFromProductionList(const Protocol::Job *job, GUIG::Controller *c)
{
  /* Annonce qu'un joueur a annulé la production d'une amelioration */
  Kernel::ID::id_t playerID;
  Kernel::Serial type, amelioration;
  Protocol::JobResolver::getInstance()->removeAmeliorationFromProductionQueue(job, playerID, type, amelioration);
  /* player->removeFromQueue(type, amelioration); */

  c->game_ameliorationDeletedFromProductionList(playerID, type, amelioration);
}

void		Client::JobController::ping(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'un joueur allié a ping sur la map */
  Kernel::ID::id_t playerID;
  double x, y;
  Protocol::JobResolver::getInstance()->ping(job, playerID, x, y);

  c->game_ping(playerID, x, y);
  MUST_IMPLEMENT
}

void		Client::JobController::playerRessources(const Protocol::Job *job, GUIG::Controller *c) {
  /* Donne les ressources d'un joueur */
  Kernel::ID::id_t id;
  unsigned int gold, wood, food;
  Protocol::JobResolver::getInstance()->playerRessources(job, id, gold, wood, food);
  /* player->setRessources */

  c->game_setRessource(id, gold, wood, food);
}

void		Client::JobController::itemAttackItem(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'un item attaque un autre */
  Kernel::ID::id_t source, target;
  Protocol::JobResolver::getInstance()->itemAttack(job, source, target);

  c->game_itemAttackItem(source, target);
}

void		Client::JobController::itemAttackZone(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'un item attaque une zone */
  Kernel::ID::id_t source;
  double x, y, z;
  Protocol::JobResolver::getInstance()->itemAttackZone(job, source, x, y, z);

  c->game_itemAttackZone(source, x, y, z);
}

void		Client::JobController::itemUseCapacityOnZone(const Protocol::Job *job, GUIG::Controller *c) {
  /* Annonce qu'une item utilise une capacité sur unz zone */
  Kernel::ID::id_t item;
  double x, y, z;
  Kernel::Serial capacity;
  Protocol::JobResolver::getInstance()->itemUseZoneCapacity(job, item, capacity, x, y, z);

  c->game_itemUseCapacityOnZone(item, x, y, z, capacity);
}

void		Client::JobController::itemUseCapacityOnItem(const Protocol::Job *job, GUIG::Controller *c) {
  /* Un item a utilisé une capacité sur un autre item */
  Kernel::ID::id_t source, target;
  Kernel::Serial capacity;
  Protocol::JobResolver::getInstance()->itemUseCapacity(job, source, target, capacity);

  c->game_itemUseCapacityOnItem(source, target, capacity);
}

void		Client::JobController::capacityUsed(const Protocol::Job *job, GUIG::Controller *c) {
  /* Un item a utilisé une capacité (no target) */
  Kernel::ID::id_t item;
  Kernel::Serial capacity;
  Protocol::JobResolver::getInstance()->itemUseCapacity(job, item, capacity);

  c->game_capacityUsed(item, capacity);
}

void		Client::JobController::capacityOnAutoOrNot(const Protocol::Job *job, GUIG::Controller *c) {
  /* Un item a activé ou non une capacité */
  Kernel::ID::id_t item;
  Kernel::Serial capacity;
  bool status;
  Protocol::JobResolver::getInstance()->activateCapacity(job, item, capacity, status);
  /* capacity->setAutomatic */
  c->game_capacityOnAutoOrNot(item, capacity, status);
}

void	Client::JobController::player(const Protocol::Job *job, GUIG::Controller *c) {
  // Job envoyé pour donner des informations sur un joueur au début de la partie
  Kernel::ID::id_t id;
  unsigned int teamID;
  Kernel::Serial race;
  Protocol::JobResolver::getInstance()->playerInformation(job, id, teamID, race);

  c->game_createNewPlayer(id, teamID, race);
}

void	Client::JobController::youAre(const Protocol::Job *job, GUIG::Controller *c) {
  // Job qui donne l'id du joueur courant, 0 si spectateur
  Kernel::ID::id_t id;
  Protocol::JobResolver::getInstance()->youAre(job, id);

  c->game_setYouAre(id);
}
