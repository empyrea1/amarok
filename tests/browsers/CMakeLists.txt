include_directories(
  ..
  ${AMAROK_SOURCE_TREE}
  ${CMAKE_BINARY_DIR}/src
  ${AMAROK_COLLECTION_SUPPORT_DIR}
)

include_directories(SYSTEM
  ${GOOGLEMOCK_INCLUDE_DIR}
  )

#------------------------ TestMasterSlaveSynchronizationJob -----------------------------

set( testsinglecollectiontreeitemmodel_SRCS
        TestSingleCollectionTreeItemModel.cpp
        ${GOOGLEMOCK_SRCS}
    )

add_executable( testsinglecollectiontreeitemmodel  ${testsinglecollectiontreeitemmodel_SRCS} )
add_test(NAME testsinglecollectiontreeitemmodel COMMAND $<TARGET_FILE:testsinglecollectiontreeitemmodel>)
ecm_mark_as_test(testsinglecollectiontreeitemmodel)

add_dependencies( testsinglecollectiontreeitemmodel amarokcore )
add_dependencies( testsinglecollectiontreeitemmodel amaroklib )

target_link_libraries(testsinglecollectiontreeitemmodel
                        amarokcore
                        amaroklib

                        Qt5::Gui
                        KF5::ThreadWeaver
                        Qt5::Test
                        Qt5::Core
                        ${GOOGLEMOCK_LIBRARIES})
