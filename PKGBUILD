# Maintainer: Daniel McGuire <danielmcguire23@icloud.com>
pkgname=sourcesearch
pkgver=1.0.0
pkgrel=1
pkgdesc="Searches Source Code for matching words."
arch=('any')
url="https://github.com/DanielLMcGuire/Source-Scanner"
license=('MIT')
depends=()
source=("https://github.com/DanielLMcGuire/Source-Scanner/archive/refs/tags/${pkgver}.tar.gz")
md5sums=('SKIP')  # Bypass checksum verification for testing

build() {
  cd "$srcdir/${pkgname}-${pkgver}"
  make
}

package() {
  cd "$srcdir/${pkgname}-${pkgver}"
  install -Dm755 "bin/sourcesearch.out" "$pkgdir/usr/bin/sourcesearch"
}