import { type TimeStamp } from './base.d';
import Project from './project.d';

export interface TabItem {
  project: Project;
  updated_time: TimeStamp;
}