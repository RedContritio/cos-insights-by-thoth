import { type UserID } from "./base.d";

export enum UserRole {
  COSER = 'coser',
  PHOTOGRAPHER = 'photographer',
  ADMIN = 'admin',
}


export class User {
  id: UserID;
  username: string;
  roles: UserRole[];

  constructor(id: UserID, username: string, roles: UserRole[]) {
    this.id = id;
    this.username = username;
    this.roles = roles;
  }
}

export default User;
