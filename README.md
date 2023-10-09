# Polar

Polar is a simple HTTP server written in C++.

## Requirements

- C++20
- Meson
- Ninja

## Installation

1. Clone the repository:

```sh
git clone https://github.com/Jabolol/polar.git .
```

2. Configure the project:

```sh
meson setup build
```

3. Compile and install the project:

```sh
cd build && ninja
```

4. Run the server:

```sh
./polar ./example_file
```

## Usage

Currently, `polar` only supports serving files. To serve a file, run:

```sh
0.0.2-alpha :: ./polar ./path/to/file
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file
for details.
