//
// Created by countzero on 9/1/22.
//

#ifndef DCHRONO_H
#define DCHRONO_H

namespace dchrono
{
    using Sec = std::chrono::duration<double>;
    using Ms = std::chrono::duration<double, std::milli>;
    using Us = std::chrono::duration<double, std::micro>;
    using Ns = std::chrono::duration<double, std::nano>;
}


#endif //DCHRONO_H
