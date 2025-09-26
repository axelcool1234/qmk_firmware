{
  description = "QMK Environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
      ...
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
        compile = pkgs.writeShellScriptBin "compile" ''
          #!/usr/bin/env bash
          set -euo pipefail
          qmk compile -kb beekeeb/piantor -km "$@"
        '';
      in
      with pkgs;
      {
        devShells.default = mkShell {
          packages = [
            qmk
            keymapviz
            vial

            compile
          ];
          shellHook = ''
            cd keyboards/beekeeb/piantor/keymaps
          '';
        };
      }
    );
}
