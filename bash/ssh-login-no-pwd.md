## 1.use ssh-keygen tool to generate ssh keyword
`ssh-keygen -t rsa`
## 2.use ssh-copy-id command to send the ssh public key to other server
`ssh-copy-id -i ~/.ssh/id_rsa.pub user@host`

