//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)


#ifndef  __ZMQ_SINKS_H
#define __ZMQ_SINKS_H

#include "../details/file_helper.h"
#include "../details/null_mutex.h"
#include "../fmt/fmt.h"
#include "base_sink.h"
#include "../details/zhelpers.h"

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <mutex>
#include <string>

namespace spdlog {
    namespace sinks {
/*
 * A ZMQ Push sink that will connect to a pull server.
 */
        template<class Mutex>
        class zmq_sink SPDLOG_FINAL : public base_sink<Mutex> {
        public:
            /// ZMQ_SINK will connect to a pull zmq socket over tcp
            /// ZMQ_SINK will use the default port of 5056
            /// ZMQ_SINK will drop the log messages after the buffer is full.
            /// ZMQ_SINK can be forced to flush messages immediately.
            explicit zmq_sink(const std::string self_id, const std::string &logserver, int port = 5056,
                              bool blocking_nature = false)
                    : _self_id(self_id), _force_flush(false), _zmq_context(1), _push(_zmq_context, ZMQ_PUSH) {

                //@todo:check that the destination address is correct
                //@todo: check that the port is within range.
                _destinationAddress = std::string("tcp://") + logserver + ":" + std::to_string(port);
                _push.connect(_destinationAddress);
                set_blocking_nature(blocking_nature);
            }

            void set_force_flush(bool force_flush) {
                _force_flush = force_flush;
            }

            void set_blocking_nature(bool blocking_nature) {
                _blocking_nature = blocking_nature;
                if (!blocking_nature) {
                    int option = 0;
                    _push.setsockopt(ZMQ_SNDTIMEO, &option, sizeof(option));
                } else {
                    int option = -1;
                    _push.setsockopt(ZMQ_SNDTIMEO, &option, sizeof(option));
                }

            }

        protected:
            void _sink_it(const details::log_msg &msg) override {
                auto data = msg.formatted.data();
                s_sendmore(_push, _self_id);
                s_send(_push, data);

                if (_force_flush) {
                    _file_helper.flush();
                }
            }

            void _flush() override {
                /// flush does not do anything right now.
            }

        private:
            std::string _self_id;
            bool _force_flush;
            bool _blocking_nature;
            zmq::context_t _zmq_context;
            zmq::socket_t _push;
            std::string destinationAddress;
        };

        // using simple_file_sink_mt = simple_file_sink<std::mutex>;
        // using simple_file_sink_st = simple_file_sink<details::null_mutex>;


    } // namespace sinks
} // namespace spdlog

#endif