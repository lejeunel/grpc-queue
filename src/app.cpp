#include "include/app.h"

void App::run(int const &n_items) {

  std::cout << "app pushing tasks in queue" << std::endl;
  for (int i = 0; i < n_items; ++i) {
    std::cout << "Pushing " << i << "\n";
    m_q->push(i);
  }

  std::cout << "app spawning worker thread" << std::endl;
  std::thread worker_thread(*m_worker);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  m_q->push(999);

  m_q->shutdown();
  worker_thread.join();
}
