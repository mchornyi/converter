#include "TaskBase.h"

using namespace task_runner;

const TaskID INVALID_ID(0);
TaskID id_counter(INVALID_ID);

TaskBase::TaskBase() : m_id( INVALID_ID )
{
    m_id = ++id_counter;
}

 TaskBase::~TaskBase()
 {

 }

 TaskID TaskBase::get_id() const
 {
     return m_id;
 }