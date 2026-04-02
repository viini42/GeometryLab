add_library(CompilerOptions INTERFACE)

# --------------------------------
# Platform settings
# --------------------------------
message(STATUS "Setting up platform = ${CMAKE_SYSTEM_NAME}")
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
  target_compile_definitions(CompilerOptions INTERFACE PLATFORM_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_compile_definitions(CompilerOptions INTERFACE PLATFORM_LINUX)
else()
  message(FATAL_ERROR "Unsupported platform")
endif()

# --------------------------------
# Compiler settings
# --------------------------------
message(STATUS "Setting up compiler flags = ${CMAKE_CXX_COMPILER_ID}:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}")
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(CompilerOptions INTERFACE
      /Wall                        # Enable most common warnings
      /W4                          # Set warning level 4 (highest warning level)
      $<$<CONFIG:Release>:/WX>     # Treat warnings as errors
  )
  if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(CompilerOptions PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(CompilerOptions INTERFACE
      -Wall                        # Enable most common warnings
      -Wextra                      # Enable extra warnings
      -Wpedantic                   # Issue all the warnings demanded by strict ISO C and ISO C++
      -Werror                      # Treat warnings as errors
      -Wconversion                 # Warn for implicit conversions that may change the value
      -Wsign-conversion            # Warn for signed-to-unsigned conversion
      -Wunreachable-code           # Warn if the compiler detects code that will never be executed
      -Wunused                     # Warn about variables or functions that are defined but never used
      -Wunused-parameter           # Warn about unused function parameters
      -Wunused-variable            # Warn about unused variables
      -Wfloat-equal                # Warn if floating-point values are compared for equality
      -Wshadow                     # Warn whenever a local variable shadows another local variable
      -Wuninitialized              # Warn about uninitialized variables
      -Wmaybe-uninitialized        # Warn about variables that may be uninitialized
      -Wunused-label               # Warn when a label is declared but not used
      -Wsuggest-override           # Warn if a function could be marked override
      -Wnon-virtual-dtor           # Warn when a class has a non-virtual destructor

      # Undefined Behavior & Safety
      -Wstrict-overflow=5          # Warn about cases where the compiler optimizes based on assumed no overflow
      -Wnull-dereference           # Warn if a null dereference is detected
      -Wformat=2                   # Extra format string checks (implies -Wformat-security)
      -Wformat-overflow=2          # Warn about buffer overflows in sprintf/snprintf
      -Wformat-truncation=2        # Warn about output truncation in snprintf
      -Wstack-protector            # Warn about functions not protected by stack-smashing protection

      # C++ Correctness
      -Wold-style-cast             # Warn for C-style casts (use static_cast etc. instead)
      -Wcast-align                 # Warn when a pointer is cast such that alignment is increased
      -Wcast-qual                  # Warn when a cast drops a type qualifier like const
      -Woverloaded-virtual         # Warn when a derived class hides a virtual function
      -Wmissing-declarations       # Warn if a function is defined without a prior declaration

      # Resource & Object Lifetime
      -Wdangling-else              # Warn about dangling else ambiguities
      -Wzero-as-null-pointer-constant  # Warn when 0 is used as a null pointer (use nullptr)
      -Wextra-semi                 # Warn about superfluous semicolons after member declarations

      # Integer & Arithmetic
      -Wdouble-promotion           # Warn when float is implicitly promoted to double
      -Warith-conversion           # Warn about implicit conversions in arithmetic operations
      -Wshift-overflow=2           # Warn about shift operations that overflow

      # Switch / Control Flow
      -Wimplicit-fallthrough       # Warn when a switch case falls through without [[fallthrough]]
      -Wswitch-default             # Warn when a switch statement does not have a default case
      -Wswitch-enum                # Warn when a switch on an enum doesn't cover all values

      # Modern C++ Hygiene
      -Wuseless-cast               # Warn when casting to the same type (GCC-specific, great for C++23)
      -Wsuggest-final-types        # Warn if a class could be marked final
      -Wsuggest-final-methods      # Warn if a virtual method could be marked final
      -Wredundant-decls            # Warn if something is declared more than once
      -Wmisleading-indentation     # Warn when indentation doesn't match the block structure

      $<$<CONFIG:Debug>:-fsanitize=address,undefined>
      $<$<CONFIG:Debug>:-fno-omit-frame-pointer>

  )
  target_link_options(CompilerOptions INTERFACE
      $<$<CONFIG:Debug>:-fsanitize=address,undefined>
      $<$<CONFIG:Debug>:-static-libasan>        # Statically link ASan
      $<$<CONFIG:Debug>:-static-libubsan>       # Statically link UBSan
  )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC" OR CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
    target_compile_options(CompilerOptions INTERFACE
        -Wall                        # Enable most warning messages
        -Wextra                      # Enable some extra warning messages
        -Wpedantic                   # Warn about non-portable constructs
        -Werror                      # Treat warnings as errors
        -Wshadow                     # Warn whenever a local variable shadows another local variable
        -Wconversion                 # Warn for implicit conversions that may change the value
        -Wsign-conversion            # Warn for implicit conversions that may change the sign
        -Wformat=2                   # Check printf/scanf format strings
        -Wundef                      # Warn if an undefined identifier is evaluated in an #if directive
        -Wunreachable-code           # Warn if code will never be executed
        -Wunused                     # Warn about unused functions, variables, etc.

        # C++ Correctness
        -Wold-style-cast                 # Warn for C-style casts
        -Wcast-align                     # Warn when cast increases alignment requirement
        -Wcast-qual                      # Warn when cast drops a type qualifier like const
        -Wnon-virtual-dtor               # Warn when class has non-virtual destructor
        -Woverloaded-virtual             # Warn when a derived class hides a virtual function
        -Wsuggest-override               # Warn if a function could be marked override
        -Wzero-as-null-pointer-constant  # Warn when 0 is used instead of nullptr
        -Wextra-semi                     # Warn about unnecessary semicolons

        # Integer & Arithmetic
        -Wdouble-promotion               # Warn when float is implicitly promoted to double
        -Wshift-overflow                 # Warn when shift overflows
        -Wshorten-64-to-32               # Warn when 64-bit value is implicitly truncated to 32-bit (Clang-specific)

        # Control Flow
        -Wimplicit-fallthrough           # Warn when a switch case falls through without [[fallthrough]]
        -Wswitch-enum                    # Warn when a switch on an enum doesn't cover all values
        -Wswitch-default                 # Warn when a switch statement does not have a default case

        # Null & Memory Safety
        -Wnullable-to-nonnull-conversion # Warn when nullable pointer is passed as nonnull (Clang-specific)
        -Wnull-dereference               # Warn if a null dereference is detected

        # Modern C++ Hygiene
        -Wmissing-declarations           # Warn if a function is defined without a prior declaration
        -Wredundant-decls                # Warn if something is declared more than once
        -Wmisleading-indentation         # Warn when indentation doesn't match block structure
        -Wheader-hygiene                 # Warn about using namespace in headers (Clang-specific)

        # Sanitizers
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
        $<$<CONFIG:Debug>:-fsanitize=implicit-conversion>  # Clang-specific, catches more conversion bugs
        $<$<CONFIG:Debug>:-fsanitize=nullability>          # Clang-specific, runtime nullability checks
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
    )
    target_link_options(CompilerOptions INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
    )
  else()
    message(FATAL_ERROR "Unsupported CLANG frontend (CMAKE_CXX_COMPILER_FRONTEND_VARIANT = ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})")
  endif()
else()
  message(FATAL_ERROR "Unsupported compiler (CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID})")
endif()