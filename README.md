# Ruble Converter

![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-6-41CD52?logo=qt&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%E2%89%A5%203.28-064F8C?logo=cmake&logoColor=white)

A desktop currency converter built with **C++20** and **Qt6** (Widgets, Network), featuring live exchange rates, a searchable currency picker, and a themeable UI. Built with an MVC-style architecture, with a view interface (`IExchangeView`) decoupling the controller from the concrete Qt widgets.

> **Cross-platform:** builds and runs on Windows, Linux, and macOS — the codebase has no platform-specific code, relying only on Qt6 and CMake.

## Features

- Two-way conversion between any pair of currencies
- Quick-pick segmented buttons for common currencies (`RUB`, `USD`, `EUR`) plus a searchable dropdown covering 150+ currencies, with full currency names always shown (never truncated)
- One-click swap between the "have" and "want" currencies
- Live exchange rates fetched on startup from the [Frankfurter API](https://www.frankfurter.dev/) (ECB reference rates)
- Custom Qt Style Sheet theme, fully defined in a single `.qss` resource

## Build

**Requirements:** C++20 compiler, CMake ≥ 3.28, Qt6 (`Core`, `Widgets`, `Network`)

```bash
git clone <repo_url>
cd <project_folder>
cmake -S . -B build -DCMAKE_PREFIX_PATH=<path_to_Qt6>
cmake --build build -j
```

Run the `RubleConverter` executable from the `build` folder.

## Roadmap

- [ ] Historical rates (pick a date, not just the latest)
- [ ] Custom/configurable quick-pick currencies instead of the fixed `RUB` / `USD` / `EUR` set
- [ ] Unit tests for `CurrencyConverter` and `CurrencyFetcher`
