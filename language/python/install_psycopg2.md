## python3 安装 psycopg2
### centos环境下
* `sudo yum install postgresql postgresql-devel`
  * 只有安装了这两个依赖才可以安装psycopg2
* `sudo pip3 install psycopg2`

## python2 安装psycopg2
```
wget https://files.pythonhosted.org/packages/a4/c8/9a7a47f683d54d83f648d37c3e180317f80dc126a304c45dc6663246233a/setuptools-36.5.0.zip
unzip setuptools-36.5.0.zip
cd setuptools-36.5.0
python setup.py install
```
