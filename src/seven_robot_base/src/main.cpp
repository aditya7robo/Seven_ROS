/****************************************************************************
 * *	Copyright (C) 2019-20122 Seven Robotics. All rights reserved.
 * *	Author: Mohammed Talha Arif  <mtalha@sevenrobotics.in>
 * *
 * *  Redistribution and use in source and binary forms, with or without
 * *  modification, are permitted provided that the following conditions
 * *  are met:
 * *
 * *  1. Redistributions of source code must retain the above copyright
 * *     notice, this list of conditions and the following disclaimer.
 * *  2. Redistributions in binary form must reproduce the above copyright
 * *     notice, this list of conditions and the following disclaimer in
 * *     the documentation and/or other materials provided with the
 * *     distribution.
 * * 	3. Neither the name Seven Robotics nor the names of its contributors
 * * 		 may be used to endorse or promote products derived from this
 * * 		 software without specific prior written permission.
 * *
 * *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * *  POSSIBILITY OF SUCH DAMAGE.
 * *
 * ****************************************************************************/

#include <assert.h>
#include <glib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <gattlib.h>
#include <ros/ros.h>
#include <thread>
#include <seven_robotics_msgs/Led.h>
#include <seven_robotics_msgs/CanAlive.h>

static GMainLoop *m_main_loop;
static delegate<void (void* x)> disconnectHandlerDelegate;

static void notification_handler(const uuid_t *uuid, const uint8_t *data, size_t data_length, void *user_data)
{
    ROS_INFO("Notification Handler %p: ", user_data);
    for (int i = 0; i < data_length; i++)
    {
        ROS_INFO("%02x ", data[i]);
    }
    ROS_INFO("\n");
}

static void disconnect_handler(void *x)
{
    printf("Disconnected %p\n", x);
    disconnected = true;
}

static void on_user_abort(int arg)
{
    g_main_loop_quit(m_main_loop);
    ros::shutDown();
}

class robotLedController
{
private:
    ros::NodeHandle& node;
    ros::Subscriber gaugeAliveSub;
    ros::Subscriber motorControllerAliveSub;
    ros::Subscriber ledAliveSub;
    ros::Publisher ledPub;
    ros::Time gaugeTimeStamp;
    ros::Time motorTimeStamp;
    ros::Time ledTimeStamp;

    bool gaugeCanAliveOnce = false;
    bool motorCanAliveOnce = false;
    bool ledCanAliveOnce = false;
    bool firstUpdateSent = false;

    ros::Time timeSinceInit;

public:
    bool shouldStop = false;
    std::thread canHeartBeatMonitor;

    robotLedController(ros::Node& _node) : node{_node}
    {
        timeSinceInit = ros::Time::now();
        gaugeAliveSub = node.subscribe("/CANBatteryAlive", 10, &robotLedController::gaugeCallback, this, ros::TransportHints().tcpNoDelay());
        motorControllerAliveSub = node.subscribe("/CANMotorAlive", 10, &robotLedController::motorCallback, this, ros::TransportHints().tcpNoDelay());
        ledAliveSub = node.subscribe("/CANLedAlive", 10, &robotLedController::ledCallback, this, ros::TransportHints().tcpNoDelay());

        canHeartBeatMonitor = std::thread([&]()
{
    while (!shouldStop)
    {
        if (!firstUpdateSent)
        {
            if (gaugeCanAliveOnce && motorCanAliveOnce && ledCanAliveOnce)
            {
                seven_robotics_msgs::Led ledMsg;
                ledMsg.colors.r = 0;
                ledMsg.colors.g = 125;
                ledMsg.colors.b = 0;
                ledMsg.effect = seven_robotics_msgs::Led::LED_SOLID_EFFECT;
                ledPub.publish(ledMsg);
                firstUpdateSent = true;
            }
            else
            {
                double diff = ros::Time::now().toSec() - timeSinceInit.toSec();
                if (diff >= 30)
                {
                    seven_robotics_msgs::Led ledMsg;
                    ledMsg.colors.r = 125;
                    ledMsg.colors.g = 0;
                    ledMsg.colors.b = 0;
                    ledMsg.effect = seven_robotics_msgs::Led::LED_SOLID_EFFECT;
                    ledPub.publish(ledMsg);
                }
            }
        }
        else
        {
            double gaugeDiff = ros::Time::now().toSec() - gaugeTimeStamp.toSec();
            if (gaugeDiff >= 2.0)
            {
                seven_robotics_msgs::Led ledMsg;
                ledMsg.colors.r = 125;
                ledMsg.colors.g = 0;
                ledMsg.colors.b = 0;
                ledMsg.effect = seven_robotics_msgs::Led::LED_BLINK_EFFECT;
                ledPub.publish(ledMsg);
            }

            double motorDiff = ros::Time::now().toSec() - motorTimeStamp.toSec();
            if (motorDiff >= 2.0)
            {
                seven_robotics_msgs::Led ledMsg;
                ledMsg.colors.r = 125;
                ledMsg.colors.g = 0;
                ledMsg.colors.b = 0;
                ledMsg.effect = seven_robotics_msgs::Led::LED_BLINK_EFFECT;
                ledPub.publish(ledMsg);
            }

            double ledDiff = ros::Time::now().toSec() - ledTimeStamp.toSec();
            if (gaugeDiff >= 2.0)
            {
                seven_robotics_msgs::Led ledMsg;
                ledMsg.colors.r = 125;
                ledMsg.colors.g = 0;
                ledMsg.colors.b = 0;
                ledMsg.effect = seven_robotics_msgs::Led::LED_BLINK_EFFECT;
                ledPub.publish(ledMsg);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
});
    }

    void gaugeCallback(const seven_robotics_msgs::CanAlive &msg);
    void motorCallback(const seven_robotics_msgs::CanAlive &msg);
    void ledCallback(const seven_robotics_msgs::CanAlive &msg);
    void spin();
};

class bluetoothMonitor
{
public:
    std::thread monitorThread;
    std::thread pubThread;
    std::string bdAddr;
    bluetoothMonitor(ros::NodeHandle& _node):node{_node}
    {
        status.state = seven_robotics_msgs::BLEControllerStatus::IDLE
        disconnectHandlerDelegate = delegate<void (void *)>::from(this,&bluetoothMonitor::disconnectCallback);
        bluetoothStatusPub = node.advertise<seven_robotics_msgs::BLEControllerStatus>("/bleControllerStatus",1);
        bdAddr = node.getParam("blecontroller_mac",bdAddr);
        monitorThread = std::thread([&]()
        {
            gatt_connection_t *connection;

            while (!shouldStop)
            {
                ROS_INFO(stderr, "Attempting connection\n");
                connection = gattlib_connect(NULL, bdAddr.c_str(), GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
                if (connection == NULL)
                {
                    ROS_INFO(stderr, "Failed to connect to the bluetooth device.\n");
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    continue;
                }
                ROS_INFO(stderr, "Connected: %p\n", connection);
                disconnected = false;
                status.state = seven_robotics_msgs::BLEControllerStatus::CONNECTED;
                gattlib_register_on_disconnect(connection, disconnect_handler, connection);

                while (!disconnected)
                {
                    fprintf(stderr, "Still connected...\n");
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }

                gattlib_disconnect(connection);

                fprintf(stderr, "Finished everything, retrying...\n");
                std::this_thread::sleep_for(std::chrono::seconds(1));

                return NULL;
            }

            gattlib_disconnect(connection);

        });

        pubThread = std::thread([&](){
            while(!shouldStop)
            {
                {
                    std::lock_guard<std::mutex> lock(pubMutex);
                    bluetoothStatusPub.publish(status);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }

void disconnectCallback(void* x)
{
    std::lock_guard<std::mutex> lock(pubMutex);
    seven_robotics_msgs::BLEControllerStatus msg;
    status.state = seven_robotics_msgs::BLEControllerStatus::DISCONNECTED
    disconnected = true;
}

void stopThread() {
    shouldStop = true;
}

private:
ros::Publisher bluetoothStatusPub;
seven_robotics_msgs::BLEControllerStatus status;
ros::NodeHandle& node;
std::mutex pubMutex;
bool shouldStop = false;
bool disconnected = false;
};

void robotLedController::gaugeCallback(const seven_robotics_msgs::CanAlive &msg)
{
    if (!gaugeCanAliveOnce)
        gaugeCanAliveOnce = true;

    gaugeTimeStamp = msg.header.stamp;
}

void robotLedController::motorCallback(const seven_robotics_msgs::CanAlive &msg)
{
    if (!motorCanAliveOnce)
        motorCanAliveOnce = true;

    motorTimeStamp = msg.header.stamp;
}

void robotLedController::ledCallback(const seven_robotics_msgs::CanAlive &msg)
{
    if (!ledCanAliveOnce)
        ledCanAliveOnce = true;

    ledTimeStamp = msg.header.stamp;
}

void robotLedController::spin()
{
    while (ros::ok())
    {
        ros::spinOnce();
    }
    shouldStop = true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ledControllerNode");
    ros::nodeHandle nh;
    robotLedController controller(nh);

    //clean the connection and node when sigint received
    signal(SIGINT, on_user_abort);
	
    m_main_loop = g_main_loop_new(NULL, 0);
	g_main_loop_run(m_main_loop);
    
    while(ros::ok())
    {
        ros::spinOnce();
    }
    
    controller.stopThread();
    bleMonitor.stopThread();
    controller.canHeartBeatMonitor.join();
    bleMonitor.pubThread.join();
    bleMonitor.monitorThread.join();
    // In case we quit the main loop, clean the connection
    g_main_loop_unref(m_main_loop);
    return 0;
}
