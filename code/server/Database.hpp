//
// Created by david on 11/02/17.
//

#ifndef PROJET_DATABASE_H
#define PROJET_DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include "../common/Credentials.h"
#include <vector>

typedef struct RankingInfos  {
    int victories;
    std::string username;

}RankingInfos;

typedef struct PublicAccountInfos  {
    std::string victories, pnjKilled;
    std::string username;
    int ID;
}PublicAccountInfos;

class Database {

private:
    const char* filename;
    sqlite3 *db;
    int rc;

public:
    Database(const char* filename);

    static int callback_counter(void *count, int argc, char **argv, char **azColName);
    static int callback_ranking(void *ptr, int argc, char **argv, char **azColName);
    static int callback_account_usrname(void *ptr, int argc, char **argv, char **azColName);
    static int callback_account_id(void *ptr, int argc, char **argv, char **azColName);
    static int callback_FriendList(void *ptr, int argc, char **argv, char **azColName);

    int open();
    void exec(const char *query, int (*callback)(void*,int,char**,char**), void * data, char * ErrMsg );
    int insert_account(Credentials credentials);
    int get_nb_entries();
    bool is_identifiers_valid(Credentials credentials);
    std::vector<RankingInfos> getRanking();
    PublicAccountInfos getUsrInfosByUsrname(std::string);
    int getIDbyUsername(std::string username);

    std::vector<std::string> getFriendList(std::string username);
    std::vector<std::string> getFriendRequests(std::string username);
    std::vector<std::string> getPendingInvitations(std::string username);

    int sendFriendRequest(std::string username, std::string toAdd);
    int acceptFriendRequest(std::string username, std::string toAccept);
    int removeFriend(std::string username, std::string toRemove);
    int declineFriendRequest(std::string username, std::string toDecline);

    void updateAfterGameStats(int id, int pnjKilled, bool isWinner);



    virtual ~Database();


};


#endif //PROJET_DATABASE_H
