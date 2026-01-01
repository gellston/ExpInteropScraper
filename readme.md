# ExpInteropScraper

A proof-of-concept **reverse interop** bridge that lets **native C++** code call a **C# HTTPS HTML scraper** through a **C++/CLI (mixed-mode)** layer.

This repo demonstrates a pragmatic pattern:

- Keep scraping logic in **C#** (`SharpScrapperLib`)
- Hold the managed scraper instance in **C++/CLI** via `msclr::gcroot<T^>`
- Expose a clean, native-friendly **C++ wrapper** (`expInteropScrapper`) using the **pImpl** idiom
- Marshal strings across the boundary with `msclr::interop::marshal_as`

> Scope: Experimental / PoC. Designed for **Windows + MSVC** with a consistent toolchain across projects.

---

## Why this exists

Calling managed code from native code is often done via COM, .NET hosting APIs, or directly referencing C++/CLI.  
This project focuses on a lightweight alternative for internal use and prototyping:

- Native C++ consumes a normal C++ class (`expInteropScrapper`)
- The wrapper hides managed types and implementation details
- The C# implementation can evolve independently

---

## High-level architecture

```
ConsoleCpp (native)
    |
    |  expInterop::expInteropScrapper (C++ wrapper)
    v
ExpInteropScraperLib (C++/CLI mixed-mode DLL)
    |
    |  gcroot<SharpScrapperLib::SimpleScraper^>
    v
SharpScrapperLib (C#)
    |
    v
HttpClient -> HTTPS GET -> HTML string
```

---

## Solution layout

- **SharpScrapperLib** (C# Class Library)
  - `SimpleScraper.cs`
  - Implements `GetHtml(string url) -> string` (HTTPS fetch)

- **ExpInteropScraperLib** (C++/CLI mixed-mode library)
  - `expInteropScrapper.h/.cpp`
  - pImpl wrapper + managed bridge (`gcroot<SimpleScraper^>`)

- **ConsoleCpp** (Native C++ Console)
  - Demonstrates usage of the wrapper from native code

- **ConsoleCSharp** (C# Console)
  - Optional, useful for validating the C# scraper directly

---

## Core design

### 1) pImpl wrapper (native-facing)

`expInterop::expInteropScrapper` is the public, native-facing class.  
It stores a `std::unique_ptr<impl_expInteropScrapper>` and hides all managed details.

Key APIs:

- `std::string getHtml(std::string address)`
- `static std::shared_ptr<expInteropScrapper> create()`

### 2) Managed lifetime (gcroot + Dispose)

The C# object is owned by the internal implementation:

- Created with `gcnew SimpleScraper()`
- Disposed via `delete` in the C++/CLI destructor (invokes `IDisposable.Dispose()`)

### 3) String marshaling

- `std::string` → `System::String^` and back via `msclr::interop::marshal_as`

---

## Managed usage example (ConsoleCpp)

```csharp
namespace ConsoleSharp
{
    internal class Program
    {
        static void Main(string[] args)
        {


            var scrapper = new SharpScrapperLib.SimpleScraper();
            var html = scrapper.GetHtml("https://www.naver.com");

            System.Console.WriteLine(html);
        }
    }
}
```

## Native usage example (ConsoleCpp)

```cpp
#include "expInteropScrapper.h"
#include <iostream>

int main() {
    auto scraper = expInterop::expInteropScrapper::create();
    std::string html = scraper->getHtml("https://example.com");
    std::cout << html << std::endl;
    return 0;
}
```

---

## Build

### Requirements
- Windows
- Visual Studio with **C++/CLI** support
- Consistent platform across projects (**x64** recommended)

### Steps
1. Open the solution in Visual Studio
2. Select platform (x64)
3. Build the solution
4. Run `ConsoleCpp` (native) or `ConsoleCSharp` (managed test)

---

## License

MIT License — see [LICENSE](LICENSE).
