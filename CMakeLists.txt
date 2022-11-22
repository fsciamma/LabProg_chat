cmake_minimum_required(VERSION 3.23)
project(LabProg_chat)

set(CMAKE_CXX_STANDARD 14)

add_executable(LabProg_chat main.cpp Subject.h Chat.cpp Chat.h Notifier.cpp Notifier.h Observer.h User.cpp User.h Message.cpp Message.h GroupChat.cpp GroupChat.h badNotifier.cpp badNotifier.h)
