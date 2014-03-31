// C/C++ File
// AUTHOR:   kyndt
// MAIL:     clovis.kyndt@gmail.com
// FILE:     includes/GUIG/IGUIG.hpp
// ROLE:     TODO (some explanation)
// CREATED:  2014-01-01 15:01:28
// MODIFIED: 2014-01-08 14:04:26

#ifndef   __GUIG_CHATBOX_HPP__
# define  __GUIG_CHATBOX_HPP__

#include  "overlays/AOverlaySceneManager.hh"
#include  "overlays/OverlayText.hh"
#include  "overlays/OverlayImage.hh"
#include  "overlays/InputText.hh"
#include  "overlays/TextBox.hh"
#include  "GUIG/AGUIG.hpp"

namespace GUIG {
  class ChatBox: public AGUIG, public AOverlaySceneManager {
  private:
    struct Message {
      enum Type {
	PRIVATE,
	GROUP,
	ALL
      };

      Message::Type	type;
      std::string	from;
      std::string	msg;
      unsigned int	time;

      Message();
      Message(Message::Type, const std::string &, const std::string &, unsigned int);
      Message(const Message &);
      Message& operator=(const Message &);
      ~Message();
    };

    std::list<Message>	_msgs;
    InputText		*_input;
    TextBox		*_box;
    Ogre::Vector2	_winsize;

  public:
    ChatBox();
    virtual ~ChatBox();

  public:
    virtual void init(unsigned int, unsigned int);
    virtual void draw();

  public:
    void	clear();

    void	leaveGame();
    void	enterGame();

    void	recvWhisp(const std::string &from, const std::string &msg);
    void	recvGrpMsg(const std::string &from, const std::string &msg);
    void	recvMsgGlob(const std::string &from, const std::string &msg);

    void	sendMsg();

    const std::string &getInput();

  private:
    void	sendWhisp(const std::string &msg);
    void	sendMsgGrp(const std::string &msg);
    void	sendMsgGlob(const std::string &msg);
  };
}

#endif  /* ___HPP__ */
