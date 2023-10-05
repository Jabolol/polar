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

2. Build the project:

```sh
meson setup build && cd build && ninja
```

3. Run the server:

```sh
./polar example_dir
```

## Usage

```sh
0.0.1-alpha :: ./polar [file/dir] --port port
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file
for details.
