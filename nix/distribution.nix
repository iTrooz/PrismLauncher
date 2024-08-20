{ inputs, self, ... }:
{
  perSystem =
    { lib, pkgs, ... }:
    {
      packages =
        let
          ourPackages = lib.makeScope pkgs.newScope (final: self.overlays.default final pkgs);
        in
        {
          inherit (ourPackages) prismlauncher-unwrapped prismlauncher;
          default = ourPackages.prismlauncher;
        };
    };

  flake = {
    overlays.default =
      final: prev:
      let
        version = builtins.substring 0 8 self.lastModifiedDate or "dirty";
      in
      {
        prismlauncher-unwrapped = prev.callPackage ./pkg {
          inherit (inputs) libnbtplusplus;
          inherit version;
        };

        prismlauncher = final.callPackage ./pkg/wrapper.nix { };
      };
  };
}
