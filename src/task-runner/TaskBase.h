#pragma once

#include "common/common.h"

namespace task_runner
{
using TaskID = uint32_t;

class TaskBase
{
public:
    TaskBase( );
    TaskBase( const TaskBase& ) = delete;
    TaskBase& operator=( const TaskBase& ) = delete;
    virtual ~TaskBase( );

    TaskID get_id( ) const;

private:
    TaskID m_id;
};
}  // namespace task_runner
