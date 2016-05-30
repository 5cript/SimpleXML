#pragma once

#include "../utility/sxml_attribute.hpp"
#include "sxml_parse_options.hpp"
#include "sxml_generic_parser.hpp"

namespace SXML
{
    #define GET_VALUE(TYPE, NAME, TEMP, TAG_VALUE) \
    if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IgnoreAllError || \
        options.invalidPathHandler == InvalidPathHandlingBehaviour::Tag) \
    { \
        value = {}; \
        auto opt = object.tree.get_optional <TYPE> (NAME); \
        if (!opt) { \
            if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IgnoreAllError) \
                return; \
            else { \
                value = TAG_VALUE; \
                return; \
            } \
        } \
        TEMP = opt.get(); \
    } \
    else \
    { \
        TEMP = object.tree.get <TYPE> (NAME); \
    }
    // MAKRO END

    #define GET_CHILD(NAME, RESULT, TAG_VALUE) \
    decltype(object.tree) RESULT;\
    if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IgnoreAllError || \
        options.invalidPathHandler == InvalidPathHandlingBehaviour::Tag) \
    { \
        value = {}; \
        auto opt = object.tree.get_child_optional (NAME); \
        if (!opt) { \
            if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IgnoreAllError) \
                return; \
            else { \
                value = TAG_VALUE; \
                return; \
            } \
        } \
        RESULT = opt.get(); \
    } \
    else \
    { \
        RESULT = object.tree.get_child (NAME); \
    }
    // MAKRO END

    #define DEFAULT_PROPERTY_ERROR_HANDLER(DEFAULT_VALUE, TAG_VALUE)		\
	switch (options.invalidPropertyHandler) {								\
		case (InvalidPropertyHandlingBehaviour::Default):		\
			value = DEFAULT_VALUE;								\
			return;												\
		case (InvalidPropertyHandlingBehaviour::Tag):			\
			value = TAG_VALUE;									\
			return;												\
		case (InvalidPropertyHandlingBehaviour::IgnoreAllError):		\
			return;												\
		case (InvalidPropertyHandlingBehaviour::Throw):			\
			throw exc;											\
		default:												\
			return;												\
	}
	// MAKRO END

	#define DEFAULT_PATH_ERROR_HANDLER(DEFAULT_VALUE, TAG_VALUE)		\
	switch (options.invalidPathHandler) {								\
		case (InvalidPathHandlingBehaviour::Default):		\
			value = DEFAULT_VALUE;								\
			return;												\
		case (InvalidPathHandlingBehaviour::Tag):			\
			value = TAG_VALUE;									\
			return;												\
		case (InvalidPathHandlingBehaviour::IgnoreAllError):		\
			return;												\
		case (InvalidPathHandlingBehaviour::Throw):			\
			throw exc;											\
		default:												\
			return;												\
	}
	// MAKRO END

	#define DEFAULT_CATCH(DEFAULT_VALUE, TAG_VALUE) \
	catch (boost::property_tree::ptree_bad_data& exc) \
    { \
        DEFAULT_PROPERTY_ERROR_HANDLER(DEFAULT_VALUE, TAG_VALUE); \
    } \
    catch (boost::property_tree::ptree_bad_path& exc) \
    { \
        DEFAULT_PATH_ERROR_HANDLER(DEFAULT_VALUE, TAG_VALUE); \
    }
    // MAKRO END
}
