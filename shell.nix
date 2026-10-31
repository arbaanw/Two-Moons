{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
    gcc
    python3
    python313Packages.numpy
    python313Packages.pillow
    python313Packages.matplotlib
    eigen
  ];

  NIX_CFLAGS_COMPILE = "-I${pkgs.eigen}/include/eigen3";
}
