#include <gtest/gtest.h>
#include <cxxopts.hpp>

#include <clipper/config.hpp>

int main(int argc, char** argv) {
  cxxopts::Options options("libclipper_tests", "LibClipper tests");
  options.add_options()("p,redis_port", "Redis port",
                        cxxopts::value<int>()->default_value("-1"));
  options.parse(argc, argv);
  int redis_port = options["redis_port"].as<int>();
  // means the option wasn't supplied and an exception should be thrown
  if (redis_port == -1) {
    std::cerr << options.help() << std::endl;
    return -1;
  }

  clipper::Config& conf = clipper::get_config();
  conf.set_redis_port(options["redis_port"].as<int>());
  conf.set_task_execution_threadpool_size(2);
  conf.ready();
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
