#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan)
{
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const
{
    return this->username;
}

const std::string &Profile::getEmail() const
{
    return this->email;
}

SubscriptionPlan Profile::getPlan() const
{
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists()
{
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings()
{
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers()
{
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan)
{
    this->plan = plan;
}

void Profile::followProfile(Profile *profile)
{
    following.insertAtTheEnd(profile);
    (*profile).followers.insertAtTheEnd(this);
}

void Profile::unfollowProfile(Profile *profile)
{
    int i = 0;
    while (1)
    {
        if (following.getNodeAtIndex(i)->data == profile)
            break;
        else
            i++;
    }
    following.removeNode(following.getNodeAtIndex(i));

    int j = 0;
    while (1)
    {
        if ((*profile).followers.getNodeAtIndex(j)->data == this)
            break;
        else
            j++;
    }
    (*profile).followers.removeNode((*profile).followers.getNodeAtIndex(j));
}

void Profile::createPlaylist(const std::string &playlistName)
{
    Playlist temp = Playlist(playlistName);
    playlists.insertAtTheEnd(temp);
}

void Profile::deletePlaylist(int playlistId)
{
    int i = 0;
    while (1)
    {
        if ((playlists.getNodeAtIndex(i)->data).getPlaylistId() == playlistId)
            break;
        else
            i++;
    }
    playlists.removeNode(playlists.getNodeAtIndex(i));
}

void Profile::addSongToPlaylist(Song *song, int playlistId)
{
    (*getPlaylist(playlistId)).addSong(song);
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId)
{
    (*getPlaylist(playlistId)).dropSong(song);
}

Playlist *Profile::getPlaylist(int playlistId)
{
    int i = 0;
    while (1)
    {
        if ((playlists.getNodeAtIndex(i)->data).getPlaylistId() == playlistId)
            break;
        else
            i++;
    }
    return &(playlists.getNodeAtIndex(i)->data);
}

LinkedList<Playlist *> Profile::getSharedPlaylists()
{
    LinkedList<Playlist *> result;
    int sizeFollowing = following.getSize();

    for (int j = 0; j < sizeFollowing; j++)
    {
        for (int k = 0; k < (*following.getNodeAtIndex(j)->data).playlists.getSize(); k++)
        {
            if ((*following.getNodeAtIndex(j)->data).playlists.getNodeAtIndex(k)->data.isShared() == 1)
                result.insertAtTheEnd(&(*following.getNodeAtIndex(j)->data).playlists.getNodeAtIndex(k)->data);
        }
    }
    return result;
}

void Profile::shufflePlaylist(int playlistId, int seed)
{
    (*getPlaylist(playlistId)).shuffle(seed);
}

void Profile::sharePlaylist(int playlistId)
{
    (*getPlaylist(playlistId)).setShared(1);
}

void Profile::unsharePlaylist(int playlistId)
{
    (*getPlaylist(playlistId)).setShared(0);
}

bool Profile::operator==(const Profile &rhs) const
{
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const
{
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile)
{
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge)
    {
        os << " plan: "
           << "free_of_charge"
           << " |";
    }
    else if (profile.plan == premium)
    {
        os << " plan: "
           << "premium"
           << " |";
    }
    else
    {
        os << " plan: "
           << "undefined"
           << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode)
    {
        do
        {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode)
                os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode)
    {
        do
        {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode)
                os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode)
    {
        do
        {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode)
                os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
