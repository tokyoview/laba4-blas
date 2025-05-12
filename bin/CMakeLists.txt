file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.cpp")#Добавляем в переменную srcs все файлы с расширением .cpp
add_executable(${application} ${srcs} ${hdrs}) #Создаем проект
target_link_libraries(${application} ${library}) #Подключаем к проекту библиотеку
target_link_libraries(${application} ${CURSES_LIBRARIES})
