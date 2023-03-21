#include "filter_pipeline_factory.h"

#include <stdexcept>

namespace FilterFactories {
    BaseFilter* MakeBlurFilter(const FilterDescriptor& fd) {
        if (fd.filter_name != "blur") {
            throw std::invalid_argument("wrong blur filter descriptor");
        }
        if (fd.filter_params.empty()) {
            throw std::invalid_argument("wrong blur filter params size");
        }
        // int param1 = std::stoi(fd.filter_params[0]);
        // Тут конвертируем string_view в инты, гуглим. (вынести в хелп функцию)
        // Можно вынести в модуль utils, с подходящими функциями. В классе utils это будет статическая функция
        // return new BlurFilter(param1);
        return new BlurFilter;  // Сырой указатель, значит память надо будет удалять
    }

    BaseFilter* MakeCropFilter(const FilterDescriptor& fd) {
        if (fd.filter_name != "crop") {
            throw std::invalid_argument("wrong crop filter descriptor");
        }
        if (fd.filter_params.empty()) {
            throw std::invalid_argument("wrong crop filter params size");
        }
        return new CropFilter;
    }
}

void FilterPipelineFactory::AddFilterMaker(std::string_view name, FilterFactory factory) {
    filter_to_makers_.insert({name, factory});
}

FilterPipelineFactory::FilterFactory FilterPipelineFactory::GetFilterFactoryMaker(std::string_view name) const {
    // auto it = filter_to_makers_.find(name); auto меняем на более понятную штуку:
    FilterToMakerMap::const_iterator it = filter_to_makers_.find(name);
    if (it != filter_to_makers_.end()) {
        return it->second;
    }
    return nullptr;
}

BaseFilter* FilterPipelineFactory::CreateFilter(const FilterDescriptor& descriptor) const {
    // this - это fpf из TEST3
    FilterFactory gear = /*this->*/GetFilterFactoryMaker(descriptor.filter_name);
    if (!gear) {
        return nullptr;
    }
    BaseFilter* current_filter = gear(descriptor);  // осознать.
    return current_filter;
}
