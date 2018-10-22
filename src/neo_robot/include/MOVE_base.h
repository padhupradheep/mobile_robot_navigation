/*
 *  Created on: December, 2017
 *      Authors: Djordje Vukcevic, Pradheep Krishna Muthukrishnan Padmanabhan
 */
#ifndef MOVEBASE_H_
#define MOVEBASE_H_


class MOVE_base
{
    protected:
        int sign(double x);

    public:
        MOVE_base();
        void Position_callback(const nav_msgs::Odometry::ConstPtr& msg);

        virtual ~MOVE_base();

    };

#endif