#pragma once

namespace task_runner
{
class TaskRunner;
}

namespace helpers
{
void stop_task_runner( task_runner::TaskRunner& task_runner );
long long file_size( const std::string& file_path );
}  // namespace helpers