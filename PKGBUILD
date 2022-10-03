
pkgname=Calculator
pkgver=1.0
pkgrel=1
arch=('x86_64')
pkgdir="/usr/bin/${pkgname}"
pkgdesc="Terminal and GUI calculator made with GTK4/gtkmm-4.0"
depends=('gtkmm-4.0' 'gtk4')
build() {
    cd ../
    cmake -B build # \
    cmake --build build
}

check() {
    cd ../
    ctest --test-dir build --output-on-failure
}

package() {
    cd ../
    if [ ! -d "$HOME/.local/share/calc" ]; then
    mkdir $HOME/.local/share/calc
    touch $HOME/.local/share/calc/vars.txt
    fi
    install -Dm755 build/Calculator "$pkgdir"/usr/bin/calculator
}
