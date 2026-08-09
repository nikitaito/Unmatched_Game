#ifndef SPACE_H
#define SPACE_H

#include<vector>
#include"Enums.h"
#include"fighter/SherlockHolmes.h"
#include"fighter/Dracula.h"

class Space
{
    private:
        std :: vector<Zone> zone ;
        std :: vector<int> neighbor ;
        std :: vector<int> Hidden_way;

        int id;
        
        Heroes * hero = nullptr;
        Sidekick * comrade = nullptr;
        Sidekick * token = nullptr;

    public:
        Space() = default;
        Space(int , std :: vector<int> , std :: vector<int> , std :: vector<Zone> ) ;
        void reset();

        //set and get
        void set_zone(std :: vector<Zone> &);
        void set_hero(Heroes *);
        void set_comrades(Sidekick *);
        void set_token(Sidekick *);
        void clear_token();
        void set_neighbor(std :: vector<int> & );
        void set_hidden_way(std :: vector<int> & );

        bool empty() const;
        int get_id() const;
        std :: vector<int> get_neighbor() const;
        std :: vector<int> get_Hidden_way() const;
        std :: vector<Zone> get_zone() const;
        Heroes* get_Hero() const;
        Sidekick* get_comrade() const;
        Sidekick* get_token() const;
        bool operator == (const Space &) const;


    
};



#endif