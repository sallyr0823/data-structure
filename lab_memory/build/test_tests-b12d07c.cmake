add_test( [==[Test the constructor (valgrind)]==] /workspaces/CS225-2022/cs225-fa22/lab_memory/build/test [==[Test the constructor (valgrind)]==]  )
set_tests_properties( [==[Test the constructor (valgrind)]==] PROPERTIES WORKING_DIRECTORY /workspaces/CS225-2022/cs225-fa22/lab_memory/build)
add_test( [==[Test allocate() (valgrind)]==] /workspaces/CS225-2022/cs225-fa22/lab_memory/build/test [==[Test allocate() (valgrind)]==]  )
set_tests_properties( [==[Test allocate() (valgrind)]==] PROPERTIES WORKING_DIRECTORY /workspaces/CS225-2022/cs225-fa22/lab_memory/build)
add_test( [==[Test printRooms() (valgrind)]==] /workspaces/CS225-2022/cs225-fa22/lab_memory/build/test [==[Test printRooms() (valgrind)]==]  )
set_tests_properties( [==[Test printRooms() (valgrind)]==] PROPERTIES WORKING_DIRECTORY /workspaces/CS225-2022/cs225-fa22/lab_memory/build)
add_test( [==[Test printRooms() for overall output]==] /workspaces/CS225-2022/cs225-fa22/lab_memory/build/test [==[Test printRooms() for overall output]==]  )
set_tests_properties( [==[Test printRooms() for overall output]==] PROPERTIES WORKING_DIRECTORY /workspaces/CS225-2022/cs225-fa22/lab_memory/build)
add_test( [==[Test printRooms() for individual output]==] /workspaces/CS225-2022/cs225-fa22/lab_memory/build/test [==[Test printRooms() for individual output]==]  )
set_tests_properties( [==[Test printRooms() for individual output]==] PROPERTIES WORKING_DIRECTORY /workspaces/CS225-2022/cs225-fa22/lab_memory/build)
set( test_TESTS [==[Test the constructor (valgrind)]==] [==[Test allocate() (valgrind)]==] [==[Test printRooms() (valgrind)]==] [==[Test printRooms() for overall output]==] [==[Test printRooms() for individual output]==])
