/* ===========================================================================
** Copyright (c) 2020, Infineon Technologies AG All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the <organization> nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ===========================================================================
*/
/**
 * @file ifx_bgt60_raw_data_publisher.h
 *
 * @brief Publish raw data in the form of customized message type
 *        'ifx_bgt60_device/ifx_bgt60_raw_data'
 */

#ifndef IFX_RADAR_PUBLISHER_H_
#define IFX_RADAR_PUBLISHER_H_


#include <ros/ros.h>
#include <thread>
#include <memory>

/* Generated message header file */
#include "ifx_bgt60_device/ifx_bgt60_raw_data.h"
#include "ifx_ring_buffer.h"


namespace ifx
{

class RadarPublisher
{
public:
    /**
     * @brief Construct a new Radar Publisher object
     */
    RadarPublisher() = default;
    /**
     * @brief Destroy the Radar Publisher object
     */
    ~RadarPublisher();
    /**
     * @brief Initialize RadarPublisher object
     *
     * @param node              Associated ROS node
     * @param pub_topic_name    Publish topic name
     * @param pub_queue_size    Publish queue size
     * @param buff              Buffer of data to be published
     * @return true             Initialization succeed
     * @return false            Initialization fail
     */
    bool init(ros::NodeHandle& node,
              const std::string& pub_topic_name,
              const int pub_queue_size,
              std::shared_ptr<RingBuffer<std::unique_ptr<
                ifx_bgt60_device::ifx_bgt60_raw_data> > > buff);
    /**
     * @brief Get initialization status
     */
    inline bool isRunning() { return _running; }

private:
    /**
     * @brief Get raw data from ring buffer, and publish
     *        customized message in a separate thread
     */
    void publishData();

    bool            _running = { false };
    ros::Publisher  _publisher;
    std::thread     _pub_thread;

    std::shared_ptr<RingBuffer<std::unique_ptr<ifx_bgt60_device::ifx_bgt60_raw_data> > > _buff = { nullptr };
};

} // namespace ifx
#endif // IFX_RADAR_PUBLISHER