#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan)
{
    profiles.insertAtTheEnd(Profile(email, username, plan));
}

void MusicStream::deleteProfile(const std::string &email)
{
    Profile *profil;
    int i = 0;
    int sizeFollowing, sizeFollowers;

    while (1)
    {
        if (profiles.getNodeAtIndex(i)->data.getEmail() == email)
            break;
        else
            i++;
    }
    profil = &(profiles.getNodeAtIndex(i)->data);

    sizeFollowing = (*profil).getFollowings().getSize();
    sizeFollowers = (*profil).getFollowers().getSize();

    for (int j = 0; j < sizeFollowing; j++)
        (*profil).unfollowProfile((*profil).getFollowings().getNodeAtIndex(0)->data);

    for (int k = 0; k < sizeFollowers; k++)
        (*(*profil).getFollowers().getNodeAtIndex(0)->data).unfollowProfile(profil);

    profiles.removeNode(profiles.getNodeAtIndex(i));
}

void MusicStream::addArtist(const std::string &artistName)
{
    artists.insertAtTheEnd(Artist(artistName));
}

void MusicStream::addAlbum(const std::string &albumName, int artistId)
{
    Album albumnew = Album(albumName);
    albums.insertAtTheEnd(albumnew);

    int i = 0;
    while (1)
    {
        if ((artists.getNodeAtIndex(i)->data).getArtistId() == artistId)
            break;
        else
            i++;
    }
    (artists.getNodeAtIndex(i)->data).addAlbum(&albums.getLastNode()->data);
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId)
{
    Song temp_song = Song(songName, songDuration);
    songs.insertAtTheEnd(temp_song);

    int i = 0;
    while (1)
    {
        if ((albums.getNodeAtIndex(i)->data).getAlbumId() == albumId)
            break;
        else
            i++;
    }
    (albums.getNodeAtIndex(i)->data).addSong(&songs.getLastNode()->data);
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2)
{
    int i = 0;
    int j = 0;

    while (1)
    {
        if ((profiles.getNodeAtIndex(i)->data).getEmail() == email1)
            break;
        else
            i++;
    }
    while (1)
    {
        if ((profiles.getNodeAtIndex(j)->data).getEmail() == email2)
            break;
        else
            j++;
    }

    (profiles.getNodeAtIndex(i)->data).followProfile(&(profiles.getNodeAtIndex(j)->data));
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2)
{
    int i = 0;
    int j = 0;

    while (1)
    {
        if ((profiles.getNodeAtIndex(i)->data).getEmail() == email1)
            break;
        else
            i++;
    }
    while (1)
    {
        if ((profiles.getNodeAtIndex(j)->data).getEmail() == email2)
            break;
        else
            j++;
    }

    (profiles.getNodeAtIndex(i)->data).unfollowProfile(&(profiles.getNodeAtIndex(j)->data));
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName)
{
    int i = 0;
    while (1)
    {
        if ((profiles.getNodeAtIndex(i)->data).getEmail() == email)
            break;
        else
            i++;
    }

    (profiles.getNodeAtIndex(i)->data).createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId)
{
    int i = 0;
    while (1)
    {
        if ((profiles.getNodeAtIndex(i)->data).getEmail() == email)
            break;
        else
            i++;
    }

    (profiles.getNodeAtIndex(i)->data).deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId)
{
    Profile *Profil;
    Playlist *PList;
    Song *sng;

    int i = 0;
    int j = 0;
    int k = 0;

    while (1)
    {
        if ((profiles.getNodeAtIndex(i)->data).getEmail() == email)
            break;
        else
            i++;
    }
    Profil = &profiles.getNodeAtIndex(i)->data;

    while (1)
    {
        if ((*Profil).getPlaylists().getNodeAtIndex(j)->data.getPlaylistId() == playlistId)
            break;
        else
            j++;
    }
    PList = &(*Profil).getPlaylists().getNodeAtIndex(j)->data;

    while (1)
    {
        if ((songs.getNodeAtIndex(k)->data).getSongId() == songId)
            break;
        else
            k++;
    }
    sng = &songs.getNodeAtIndex(k)->data;

    (*PList).addSong(sng);
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId)
{
    Profile *Profil;
    Playlist *PList;
    Song *sng;

    int i = 0;
    int j = 0;
    int k = 0;

    while (1)
    {
        if ((profiles.getNodeAtIndex(i)->data).getEmail() == email)
            break;
        else
            i++;
    }
    Profil = &profiles.getNodeAtIndex(i)->data;

    while (1)
    {
        if ((*Profil).getPlaylists().getNodeAtIndex(j)->data.getPlaylistId() == playlistId)
            break;
        else
            j++;
    }
    PList = &(*Profil).getPlaylists().getNodeAtIndex(j)->data;

    while (1)
    {
        if ((songs.getNodeAtIndex(k)->data).getSongId() == songId)
            break;
        else
            k++;
    }
    sng = &songs.getNodeAtIndex(k)->data;

    (*PList).dropSong(sng);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist)
{
    Profile *profil;
    int i = 0;

    while (1)
    {
        if (profiles.getNodeAtIndex(i)->data.getEmail() == email)
            break;
        else
            i++;
    }
    profil = &profiles.getNodeAtIndex(i)->data;

    if (profil->getPlan() == premium)
        return (*playlist).getSongs();
    else
    {
        LinkedList<Song *> temp;
        temp = playlist->getSongs();
        temp.insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG), 2);
        return temp;
    }
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId)
{
    Profile *Profil;
    Playlist *PList;

    int i = 0;
    int j = 0;

    while (1)
    {
        if ((profiles.getNodeAtIndex(i)->data).getEmail() == email)
            break;
        else
            i++;
    }
    Profil = &profiles.getNodeAtIndex(i)->data;

    while (1)
    {
        if ((*Profil).getPlaylists().getNodeAtIndex(j)->data.getPlaylistId() == playlistId)
            break;
        else
            j++;
    }
    PList = &(*Profil).getPlaylists().getNodeAtIndex(j)->data;

    return PList;
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email)
{
    Profile *profil;
    int i = 0;

    while (1)
    {
        if (profiles.getNodeAtIndex(i)->data.getEmail() == email)
            break;
        else
            i++;
    }
    return (profiles.getNodeAtIndex(i)->data).getSharedPlaylists();
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed)
{
    getPlaylist(email, playlistId)->shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId)
{
    Playlist *PL = getPlaylist(email, playlistId);
    PL->setShared(1);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId)
{
    Playlist *PL = getPlaylist(email, playlistId);
    PL->setShared(0);
}

void MusicStream::subscribePremium(const std::string &email)
{
    int i = 0;
    while (1)
    {
        if (profiles.getNodeAtIndex(i)->data.getEmail() == email)
            break;
        else
            i++;
    }
    profiles.getNodeAtIndex(i)->data.setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email)
{
    int i = 0;
    while (1)
    {
        if (profiles.getNodeAtIndex(i)->data.getEmail() == email)
            break;
        else
            i++;
    }
    profiles.getNodeAtIndex(i)->data.setPlan(free_of_charge);
}

void MusicStream::print() const
{
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
