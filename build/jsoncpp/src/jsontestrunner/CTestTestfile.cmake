# CMake generated Testfile for 
# Source directory: /data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner
# Build directory: /data/home/user00/code/cppserver/build/jsoncpp/src/jsontestrunner
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(jsoncpp_readerwriter "/usr/bin/python3.6" "-B" "/data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner/../../test/runjsontests.py" "/data/home/user00/code/cppserver/build/bin/jsontestrunner_exe" "/data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner/../../test/data")
set_tests_properties(jsoncpp_readerwriter PROPERTIES  WORKING_DIRECTORY "/data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner/../../test/data" _BACKTRACE_TRIPLES "/data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner/CMakeLists.txt;43;add_test;/data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner/CMakeLists.txt;0;")
add_test(jsoncpp_readerwriter_json_checker "/usr/bin/python3.6" "-B" "/data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner/../../test/runjsontests.py" "--with-json-checker" "/data/home/user00/code/cppserver/build/bin/jsontestrunner_exe" "/data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner/../../test/data")
set_tests_properties(jsoncpp_readerwriter_json_checker PROPERTIES  WORKING_DIRECTORY "/data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner/../../test/data" _BACKTRACE_TRIPLES "/data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner/CMakeLists.txt;47;add_test;/data/home/user00/code/cppserver/jsoncpp/src/jsontestrunner/CMakeLists.txt;0;")
