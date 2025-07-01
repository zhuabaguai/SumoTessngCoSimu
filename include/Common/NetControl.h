//
// Created by chenyunzhe on 2024/12/16.
//

#ifndef SUMOCOSIMUWITHTESSNG_NETCONTROL_H
#define SUMOCOSIMUWITHTESSNG_NETCONTROL_H

#include <libsumo/libtraci.h>

namespace NetControl{
    class SumoNet{
    public:
        SumoNet();
        ~SumoNet();

        std::vector<std::string> getEdgeIdList();

    private:
        std::vector<std::string> EdgeIdList;

    };

}

#endif //SUMOCOSIMUWITHTESSNG_NETCONTROL_H
