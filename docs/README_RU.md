# Общее положение

### Основное правило

Код проекта должен быть понятным и легко читаемым. Конечно, всё это относительно, но нужно стараться придерживаться этому правилу. Не нужно мудрить, нам же поддерживать этот код.

### Структура проекта

Проект модульный. Теоретически каждый модуль может быть собран отдельно от всего проекта. Модули могут иметь между собой зависимости. К примеру, в данный момент все модули зависимы от модуля `mycore`.

Все существующие модули находятся в директории `/source/` проекта Modest.

### Зависимости

Проект развивается без внешних зависимостей. Не то чтобы мне по фану писать не раз уже всеми написанные алгоритмы, вроде AVl Tree, Binary Search Tree и так далее, мне важно использовать собственный подход в создании объектов и управлении памятью.

Так же, большенство реализованных алгоритмов не являются "чистыми", логика их как-то изменена/оптимизирована под нужды проекта.

Я не против зависимостей, но зачастую всё что нужно проекту легче написать самостоятельно чем адаптировать чей-то код, лицензии.

### Платформозависимый код

Не смотря на тот факт, что проект пишется на чистом Си (C99) без внешних зависимостей реализация некоторых функций зависит от конкретной платформы. А именно: многопоточность, таймеры, ввод-вывод, блокировки (spinlock, mutex).

Для этого реализован отдельный модуль `myport` который имеет свою собственную структуру и правила сборки отличные от остальных модулей.

### Статусы

Если внутри какой-либо функции что-то может пойти "не так" то функция должна об этом однозначно сообщить.

Существует общий для всех тип `mystatus_t` (`int`) опредленный в `mycore/myosi.h`.
Каждый модель проекта Modest определяет свой диапозон статусов. Для примера,

```C
/*
...
mycore 000000..008fff; MyCORE_STATUS_OK == 0x000000
myhtml 009000..0093ff; MyHTML_STATUS_OK == 0x000000
...
*/
```
С полным списком можно ознакомится в файле `mycore/myosi.h`.

Любая функция любого модуля может возвращать любой статус. К примеру, функции из модуля `myhtml` могут возвращать статус `MyCORE_STATUS_ERROR_MEMORY_ALLOCATION`.

Два главных правила при работе со статусами:

1. Если статус равен нолю (0) то значит всё хорошо, иначе что-то пошло не так.
2. Необходимо возвращать реальные статусы. То есть, если память не выделена то вернуть `MyCORE_STATUS_ERROR_MEMORY_ALLOCATION `, а не какой-нибудь фейковый 0x100.

Перечисления (enum) статусов для конкретного модуля лучше всего держать в файле `myosi.h` в корне модуля. Для примера, `/source/myhtml/myosi.h`.

### Версии модулей

Каждый модуль должен содержать информацию о своей версии в заголовочном файле `myosi.h` в корне модуля. Для примера, `/source/myhtml/myosi.h`.

Шаблон:

```C
#define <ИМЯ-МОДУЛЯ>_VERSION_MAJOR 4
#define <ИМЯ-МОДУЛЯ>_VERSION_MINOR 0
#define <ИМЯ-МОДУЛЯ>_VERSION_PATCH 2

#define <ИМЯ-МОДУЛЯ>_VERSION_STRING MyCORE_STR(<ИМЯ-МОДУЛЯ>_VERSION_MAJOR) MyCORE_STR(.) MyCORE_STR(<ИМЯ-МОДУЛЯ>_VERSION_MINOR) MyCORE_STR(.) MyCORE_STR(<ИМЯ-МОДУЛЯ>_VERSION_PATCH)
```

### Именование функций

Для создания имени функции используется шаблон:<br>
`<название-проекта>_<путь-к-файлу>_<название-файла>_<название>(...);`

Для примера возмём функцию `mycore_utils_avl_tree_init(...)`:<br>
Найти её легко в `/source/mycore/utils/avl_tree.c`

Бывают исключения, но они обычно от лени.

### Функции Конструкторы/Деструкторы

Для API создания, инициализации, очистки, удаления объектов используется следующий шаблон:

```C
<имя-структуры> * <префикс-функции>_create(void);
mystatus_t <префикс-функции>_init(<имя-структуры>* obj);
void <префикс-функции>_clean(<имя-структуры>* obj);
void <префикс-функции>_clean_all(<имя-структуры>* obj);
<имя-структуры> * <префикс-функции>_destroy(<имя-структуры>* obj, bool self_destroy);
```

Функция инициализации объекта `*_init` может принимать любое количество аргументов.
Функции очистки `*_clean` `*_clean_all` могут возвращать любое значение, обычно void.

Если в функцию инициализации объекта `*_init` передать `NULL` в качестве первого аргумента (объект) то функция должна вернуть статус `MyCORE_STATUS_ERROR_OBJECT_NULL`.

Если при вызове функции `*_destroy` аргумент `self_destroy` указан как `true` то возвращаемое значение всегда должно быть равно `NULL`, иначе возвращается переданный в аргументах объект `obj`.

Данный подход был реализован для работы с динамически выделенными объектами и теми что находятся в стеке (статические).

Пример с динамически выделенным объектом:
```C
mycore_utils_array_t *array = mycore_utils_array_create();
mystatus_t status = mycore_utils_array_init(array, 1024);
if(status)
	exit(EXIT_FAILURE);

mycore_utils_array_destroy(array, true);
```

Пример с объектом из стека:
```C
mycore_utils_array_t array;
mystatus_t status = mycore_utils_array_init(&array, 1024);
if(status)
	exit(EXIT_FAILURE);

mycore_utils_array_destroy(&array, false);
```

Пример API инициализации для ARRAY:
```C
mycore_utils_array_t * mycore_utils_array_create(void);
mystatus_t mycore_utils_array_init(mycore_utils_array_t* array, size_t start_size);
void mycore_utils_array_clean(mycore_utils_array_t* array);
mycore_utils_array_t * mycore_utils_array_destroy(mycore_utils_array_t* array, bool self_destroy);
```

Стоит отметить, что данный подход не является абсолютным постулатом. Бывают случаи когда приходится реализовывать иное API, но всё же, в большинстве случаев именно такое. Нужно быть разумным и понимать что делаешь, а не слепо следовать правилам.

### Память

Для работы с динамической памятью используются четыре функции:
```C
void * mycore_malloc(size_t size);
void * mycore_calloc(size_t num, size_t size);
void * mycore_realloc(void* dst, size_t size);
void * mycore_free(void* dst);
```

Функции определены в `mycore/myosi.h`, реализованы в `myport/*/mycore/memory.c` и могут быть переопределены.

Из названий понятно, что это обвязки для стандартных функций `malloc, calloc , realloc, free`.
В отличии от стандартной функции `free` функция `mycore_free` возвращает значение `void *` которое всегда равно `NULL` — это своеобразный синтаксический сахар, чтобы отдельно не занулять переменные после освобождения.

К примеру,
```C
if(object->table)
	object->table = mycore_free(object->table);
```

Иначе пришлось бы писать:
```C
if(object->table) {
	 mycore_free(object->table);
	 object->table = NULL:
}
```

**О работе с памятью**

Плохим тоном считается постоянное выделение и освобождение памяти. Выделенную один раз память можно использовать многократно — об этом часто забывают.

Для примера, `myhtml` строит дерево `HTML` для которого создается много нод, 500 нод в среднем на одну страницу. У каждой ноды есть параметры. Если мы будем каждый раз дёргать malloc, а в случаи освобождения всех нод free, то программа у нас будет работать медленно, очень медленно.
Для этого в проекте созданы "менеджеры памяти/объектов" которые выделяют куски памяти под структуры и следят за ними. Читайте про `dobject` и `mraw`.

### Исходные файлы и глобальные переменные

В проекте заведено так, что каждый файл `*.h` и `*.c` отвечает за свою область.

**Плохо** когда исходный файл содержит в себе функции для работы с несколькими структурами/объектами по смыслу никак не схожие между собой.

**Файлы с данными**

Не желательно вставлять данные (глобальные переменные, "ресурсы") в один файл с описанием функций, структур. Так же не желательно вставлять ресурсы в исходный код `*.c`. Всё это может вызвать проблемы.
Для ресурсов создается отдельный файл заголовков `*.h` в котором находятся только нужные ресурсы. И включается данный файл только в исходник `*.c`.

Например:

```C
/* файл /source/mycore/utils/resources.h */

#ifndef MyCORE_UTILS_RESOURCES_H
#define MyCORE_UTILS_RESOURCES_H

static const unsigned char mycore_string_hex_to_char_map[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x00
};

#endif /* MyCORE_UTILS_RESOURCES_H */
```

```C
/* файл /source/mycore/mystring.c */

#include "mycore/utils/resources.h"

void mycore_string_some(void) 
{
	printf("%c\n", mycore_string_hex_to_char_map[0]);
}
```


### Заголовочные файлы

Все пути указываются относительно `/source/` директории. Для примера, если нам нужно подключить заголовок от модуля `myurl` который находится в каталоге `/source/myurl/`: `#include "myurl/url.h"`

При подключении любых внутренних модулей используются кавычки (U+0022 QUOTATION MARK (")).

### Шаблон для всех *.h и *.c файлов

**\*.h**

```C
/*
 Copyright (C) 2017 Alexander Borisov
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 
 Author: <почта>@<автора>.com (Имя Фамилия)
*/

#ifndef <ПУТЬ-К-ФАЙЛУ>_<НАЗВАНИЕ-ФАЙЛА>_H
#define <ПУТЬ-К-ФАЙЛУ>_<НАЗВАНИЕ-ФАЙЛА>_H

#ifdef __cplusplus
extern "C" {
#endif

/* some code */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif <ПУТЬ-К-ФАЙЛУ>_<НАЗВАНИЕ-ФАЙЛА>_H
```

**\*.c**

```C
/*
 Copyright (C) 2017 Alexander Borisov
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 
 Author: <почта>@<автора>.com (Имя Фамилия)
*/

#include "<путь к заголовку>.h"

```

### Примеры

Для значимых участков кода создаются примеры его использования в директории `/examples/`. Это помогает осваивать код и показывает его возможности.

### Тестирование

Для всего, практически для всего, должны создаваться тесты в директории `/test/`. Проект большой, регрессия наступает очень быстро. Я как автор проекта грешил тем что не создавал с самого начала тесты, уже пару раз сильно поплатился за это.

Не нужно лениться, желательно всегда прогонять созданный/изменённый код с Runtime Sanitization: address, thread, undefined behavior и прочими инструментами по анализу кода, работы программы. К примеру, Valgrind.

### Контребьютеру

Если вы создали какой либо файл или внесли значительные изменения в существующий то добавляете себя как автора в этот файл после информаци о лицензии.

```C
/*
 ...
 
 Author: <почта>@<автора>.com (Имя1 Фамилия1)
 Author: <почта>@<автора>.com (Имя2 Фамилия2)
 Author: <почта>@<автора>.com (Имя3 Фамилия3)
*/
```

Пожалуйста, не стоит вносить себя как автора если мы исправили грамматическую ошибку или поменяли имя функции/переменной.

Так же, внося добавления/изменения в существующий код вы соглашаетесь на то что ваш код будет распространяться под текущей лицензией проекта. Внесённые вами добавления/изменения могут быть изменены или удален из проекта в любое время, или распространяться вместе с проектом неопределенное время.

### Лицензия

Текущая лицензия проекта `LGPL2.1`
Смотрите файл LICENSE в корне проекта.
