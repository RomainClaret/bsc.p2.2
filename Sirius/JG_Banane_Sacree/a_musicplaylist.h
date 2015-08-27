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
    void setMusicPlaylist(QString Playlist);
    void pauseMusicPlaylist();
    void musicPlaylistRemoveIntro();
    void playMusicPlaylist();
    void playMusicPlaylist(QString playlist);

signals:

public slots:
private:

    QMediaPlayer* musicPlayer;
    QMediaPlaylist* musicPlaylist;
    QString musicQUrl;

    void run();
};

#endif // A_MUSICPLAYLIST_H
