#ifndef A_MUSICPLAYLIST_H
#define A_MUSICPLAYLIST_H

#include <QThread>

class QMediaPlayer;
class QMediaPlaylist;

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    #define MY_OS "UNIX"
#else
    #define MY_OS "OTHER"
#endif

class A_MusicPlaylist : public QThread
{
public:
    A_MusicPlaylist();

    void stopMusicPlaylist();
    void pauseMusicPlaylist();
    void musicPlaylistRemoveIntro();
    void playMusicPlaylist();

    void playMusicPlaylist(int value);
    void setMusicPlaylist(int value);

    void muteMusicPlaylist();
    void unmuteMusicPlaylist();

    void setUsable(bool usable);

    void setMusicVolume(int value);
    int getMusicVolume();

    bool getMusicUsablePlaylist();

signals:

public slots:
private:

    QMediaPlayer* musicPlayer;
    QMediaPlaylist* musicPlaylist;
    QString musicQUrl;

    bool usableMusicPlaylist;

    void run();
};

#endif // A_MUSICPLAYLIST_H
