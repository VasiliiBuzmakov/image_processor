// Этот модуль является посредником между конкретными классами фильтров и некими описаниями
// параметров объектов фильтров (filter descriptor) поэтому он знает всё и про первых, и про вторых.

#pragma once

#include "cmd_arg_parser.h"
#include "base_filters.h"
#include "map"

class FilterPipelineFactory {
public:
    // typedef BaseFilter*(*FilterFactory)(const FilterDescriptor&); // Старый вариант, можно через using:
    using FilterFactory = BaseFilter* (*)(const FilterDescriptor&);  // Указатель на функцию
    using FilterToMakerMap = std::map<std::string_view, FilterFactory>;

public:
    void AddFilterMaker(std::string_view name, FilterFactory factory);

    // По заданному имени фильтра возвращает указатель на функцию (фактори)
    FilterFactory GetFilterFactoryMaker(std::string_view name) const;

    // Создаёт фильтр по переданному ему описанию параметров командной строки
    // пользуясь шестерёнками, добавленными ранее
    BaseFilter* CreateFilter(const FilterDescriptor& descriptor) const;

protected:
    FilterToMakerMap filter_to_makers_;
};

// Дома: погуглить безымянные нейспейсы, может их тут можно использовать
// функций может быть много, поэтому используем неймспейс
namespace FilterFactories {
    // Тут мы фактически хардкодим список фильтров, доступных нашей программе.
    // Добавление нового фильтра осуществляется путём создания новой продуцирующей функции.
    BaseFilter* MakeBlurFilter(const FilterDescriptor& fd);

    BaseFilter* MakeCropFilter(const FilterDescriptor& fd);
}



