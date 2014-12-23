#include "Filter.h"

#include <math.h>
#include <iostream>

namespace Filter{

    void filterMinutiae(std::vector<Minutiae>& minutiae){
        double minDistanceForMinutiae = 10.0;
        bool same = true;
        //calculate for every minutiae the distance to all other minutiae
        for(std::vector<Minutiae>::size_type i = 0; i<minutiae.size(); i++){
            if(minutiae[i].getType() == Minutiae::Type::RIDGEENDING){
                for(std::vector<Minutiae>::size_type j = 0; j<minutiae.size(); j++){
                    if(j==i){
                        same = true;
                    }
                    if((minutiae[j].getType() == Minutiae::Type::RIDGEENDING) && !same){ //(minutiae[j].getType() == Minutiae::Type::RIDGEENDING) &&
                        double distance = euclideanDistance(minutiae[i].getLocX(), minutiae[i].getLocY(), minutiae[j].getLocX(), minutiae[j].getLocY());
                        //if the distance is to low...
                        if(distance < minDistanceForMinutiae){
                            //... then mark minutiae for erasing
                            minutiae[i].setMarkTrue();
                            minutiae[j].setMarkTrue();
                        }
                    }
                    same = false;
                }
            }
        }
        int cnt = 0;
        std::vector<Minutiae> minutiaeNew;
        //erase the marked minutiae
        for(std::vector<Minutiae>::size_type i = 0; i<minutiae.size(); i++){
            if(!minutiae[i].getMark()){
                minutiaeNew.push_back(minutiae[i]);
            }else{
                cnt++;
            }

        }
        minutiae = minutiaeNew;
        std::cout<<"Anzahl gelöschter Minutien: " << cnt << std::endl;
    }

    double euclideanDistance(int x1, int y1, int x2, int y2){
        return sqrt(((x1-x2)*(x1-x2)) + ((y1-y2)*(y1-y2)));
    }

}
