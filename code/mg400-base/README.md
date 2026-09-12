# mg400-base — moved

The Dobot MG400 base code now lives in its own repository:

**https://github.com/KKallas/mg400-base**

Clone just that, without the rest of this repo:

```sh
git clone https://github.com/KKallas/mg400-base.git
cd mg400-base
python3 -m venv .venv && source .venv/bin/activate
pip install -e .
mg400 --help
```

Setup guides (cable, IP address, enabling API mode on Mac/UTM and Windows) are
in that repo's `README.md` and `docs/`.
