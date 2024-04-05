# Full-text-search engine

<span style="font-size:1.2em;">Full-text-search gives you access to make fuzzy search on the database of books.</span>

## Usage

Follow this steps
### Build
    cmake --preset release
    cmake --build --preset release

### Run
    ./build/release/bin/

### Opitons

- You can replace `books.csv` to another file following this format
- By hand-rewriting `default.xml` options file you also can change `fts` behaviour

## Components

- <span style="font-size:1.2em;">`Indexer`</span> - Indexes the file of books - `books.csv`

- <span style="font-size:1.2em;">`ConfigParser`</span> - Parses (unpacks) config file

- <span style="font-size:1.2em;">`TextIndexAccessor`</span> - Using for make access for index that have been written via `Indexer`

- <span style="font-size:1.2em;">`Searcher`</span> - Using for build fuzzy search results for query

- <span style="font-size:1.2em;">`Common`</span> - Parses the queries for `n-grams`

- <span style="font-size:1.2em;">`Filter`</span> - Using for filter (wow!) search results

- <span style="font-size:1.2em;">`fts-csl`</span> - Command line interface

Desktop GUI coming soon...
