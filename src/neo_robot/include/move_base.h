/*
 *  Created on: December, 2017
 *      Authors: Djordje Vukcevic, Pradheep Krishna Muthukrishnan Padmanabhan
 */
#ifndef MOVEBASE_H_
#define MOVEBASE_H_

namespace goal_reach
{

class move_base
{
    protected:
        int sign(double x);

    public:
        move_base();

        virtual ~move_base();

    };

} /* namespace traj_gen */
#endif