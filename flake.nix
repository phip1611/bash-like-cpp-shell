{
  description = "phipsshell";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/24.05";
  };

  outputs =
    { self, flake-parts, ... }@inputs:
    flake-parts.lib.mkFlake { inherit inputs; } {
      flake = {

      };
      systems = inputs.nixpkgs.lib.systems.flakeExposed;
      perSystem =
        { config, pkgs, ... }:
        {
          devShells.default = pkgs.mkShell {
            inputsFrom = [ self.packages.${pkgs.system}.default ];
            packages = with pkgs; [
            ];
          };
          formatter = pkgs.nixfmt-rfc-style;
          packages.default = pkgs.stdenv.mkDerivation {
            name = "phipsshell";
            version = "0.1.0";
            src = pkgs.nix-gitignore.gitignoreSource [] ./.;
            nativeBuildInputs = with pkgs; [
              gcc
              gnumake
            ];
            buildInputs = with pkgs; [
              readline
            ];
            makeFlags = [
              "DESTDIR=$(out)"
            ];
            enableParallelBuilding = true;
          };
        };
    };
}
