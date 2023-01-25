#pragma once

/**
* Для использования одного и того же файла заголовка для dll и для клиентского приложения
*/
#ifdef STARWARSSIMULATIONSYSTEM_EXPORTS
/**
* При сборке библиотеки все классы/функции, помеченные Core_API будут расширены в __declspec(dllexport),
* что означает, что эти классы/функции будут включены в таблицу экспорта dll
*/
#define StarWarsObject __declspec(dllexport) // для включения класса/функции в таблицу экспорта dll
#define EXTERN_STARWARS
#else
/**
* При включении заговка, например, Semaphore.h в клиентский код, во время Core_API будет расширен
* в __declspec(dllimport), что означает, что этот класс будет импортирован из dll
*/
#define StarWarsObject __declspec(dllimport) // для импорта из dll в клиентский код
#define EXTERN_STARWARS extern
#endif
