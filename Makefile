##
## Makefile for  in /home/geoffrey/Projects/pfa
## 
## Made by geoffrey bauduin
## Login   <baudui_g@epitech.net>
## 
## Started on  Wed Feb  5 14:00:43 2014 geoffrey bauduin
## Last update Mon Mar 31 13:03:26 2014 geoffrey bauduin
##

NAME=			client

SRCDIR=			src/
GUIDIR=			$(SRCDIR)GUI/
GUIGDIR=		$(SRCDIR)GUIG/
BETADIR=		$(SRCDIR)beta/
APPDIR=			$(SRCDIR)applications/
OVLDIR=			$(SRCDIR)overlays/
SCNDIR=			$(SRCDIR)scene/
UTILDIR=		$(SRCDIR)Utils/
EFFDIR=			$(SRCDIR)effects/
ELEM3D=			$(SRCDIR)3DElements/

SRC=			src/Factory/Client.cpp				\
			src/Parser/Race.cpp				\
			src/Network/Manager/Client.cpp			\
			$(GUIDIR)Controller.cpp				\
			$(GUIDIR)Convers.cpp				\
			$(GUIDIR)Core.cpp				\
			$(GUIDIR)Friends.cpp				\
			$(GUIDIR)GameLoading.cpp			\
			$(GUIDIR)Group.cpp				\
			$(GUIDIR)Popup.cpp				\
			$(GUIDIR)Profile.cpp				\
			$(GUIDIR)Race.cpp				\
			$(GUIDIR)Setting.cpp				\
			$(GUIDIR)SignInUp.cpp				\
			$(GUIDIR)Tooltip.cpp				\
			$(GUIGDIR)AGUIG.cpp				\
			$(GUIGDIR)Profile.cpp				\
			$(GUIGDIR)Ressource.cpp				\
			$(GUIGDIR)ChatBox.cpp				\
			$(GUIGDIR)MiniMap.cpp				\
			$(GUIGDIR)DayNight.cpp				\
			$(GUIGDIR)Menu.cpp				\
			$(GUIGDIR)Controller.cpp			\
			$(GUIGDIR)Progress.cpp				\
			$(GUIGDIR)Annotation.cpp			\
			$(GUIGDIR)AnnotationBis.cpp			\
			$(GUIGDIR)AllyMenu.cpp				\
			$(GUIGDIR)Squad.cpp				\
			$(SRCDIR)main.cpp				\
			$(UTILDIR)graphicException.cpp			\
			$(APPDIR)Application.cpp			\
			$(EFFDIR)MoveObject.cpp				\
			$(EFFDIR)MoveOverlay.cpp			\
			$(EFFDIR)AEffect.cpp				\
			$(EFFDIR)ARepeatable.cpp			\
			$(EFFDIR)AMove.cpp				\
			$(EFFDIR)AFade.cpp				\
			$(EFFDIR)Fade.cpp				\
			$(EFFDIR)AScale.cpp				\
			$(EFFDIR)Scale.cpp				\
			$(SCNDIR)AScene.cpp				\
			$(SCNDIR)MenuScene.cpp				\
			$(OVLDIR)AOverlay.cpp				\
			$(OVLDIR)OverlayImage.cpp			\
			$(OVLDIR)OverlayText.cpp			\
			$(OVLDIR)TextBox.cpp				\
			$(OVLDIR)InputText.cpp				\
			$(OVLDIR)Button.cpp				\
			$(OVLDIR)Click.cpp				\
			$(OVLDIR)AOverlaySceneManager.cpp		\
			$(OVLDIR)MouseOverlayManager.cpp		\
			$(OVLDIR)MainMenuOverlaySceneManager.cpp	\
			$(ELEM3D)Element3DContainer.cpp			\
			src/Client/JobController.cpp			\
			$(ELEM3D)Element3DPoolManager.cpp

OBJ=			$(SRC:.cpp=.o)

DEPS =			$(OBJ:.o=.deps)

LCEGUI=			-L ./libs -L ./libs/cegui -l CEGUIBase-0 -lCEGUIOgreRenderer-0
ICEGUI=			-I./includes/Libs

LOGRE=			-L ./libs -L ./libs/OGRE -lOgreMain -lOgreOverlay
IOGRE=			-I./includes/Libs/Ogre -I./includes/Libs/Ogre/Overlay

LOIS=			-L ./libs -lOIS
IOIS=			-I./includes/Libs/OIS/

IMY=			-I./includes/ -Icommon/includes

LDFLAGS=		$(LOGRE) $(LOIS) -lboost_system -Wl,-rpath,./libs/ -Wl,-rpath,./libs/OGRE -lssl -lcrypto -lpthread  common/libs/libjson.a -Wl,-rpath,./lib/ common/hexatylaCommon.so -L./common/libs -ljson

INCLUDES=		$(IMY) $(IOGRE) $(IOIS) $(ICEGUI)

CXXFLAGS=		$(INCLUDES) -std=c++11

CXX=			g++

all:		$(NAME)

%.o:		%.cpp
		@$(CXX) -c $(CXXFLAGS) -MMD $< -o $@ -MF $(patsubst %.o, %.deps, $@) && echo "CXX\t$<"

$(NAME):	CXXFLAGS += -DCLIENT__
$(NAME):	$(OBJ)
		cd common && $(MAKE) client
		$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

hardclean:	fclean
		rm -f $(DEPS)

re:		hardclean all

-include $(DEPS)
